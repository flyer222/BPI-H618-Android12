/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.providerui.cts;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import android.app.Activity;
import android.app.Instrumentation;
import android.app.UiAutomation;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.UriPermission;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.content.res.AssetFileDescriptor;
import android.database.Cursor;
import android.net.Uri;
import android.os.Environment;
import android.os.FileUtils;
import android.os.ParcelFileDescriptor;
import android.os.storage.StorageManager;
import android.os.storage.StorageVolume;
import android.os.UserManager;
import android.provider.DocumentsContract;
import android.provider.MediaStore;
import android.provider.cts.ProviderTestUtils;
import android.providerui.cts.GetResultActivity.Result;
import android.support.test.uiautomator.By;
import android.support.test.uiautomator.BySelector;
import android.support.test.uiautomator.UiDevice;
import android.support.test.uiautomator.UiObject;
import android.support.test.uiautomator.UiObject2;
import android.support.test.uiautomator.UiObjectNotFoundException;
import android.support.test.uiautomator.UiScrollable;
import android.support.test.uiautomator.UiSelector;
import android.support.test.uiautomator.Until;
import android.system.Os;
import android.text.format.DateUtils;
import android.util.Log;

import androidx.test.InstrumentationRegistry;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import org.junit.runners.Parameterized.Parameters;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

@RunWith(Parameterized.class)
public class MediaStoreUiTest {
    private static final String TAG = "MediaStoreUiTest";

    private static final int REQUEST_CODE = 42;
    private static final long TIMEOUT_MILLIS = 30 * DateUtils.SECOND_IN_MILLIS;
    private static final String MEDIA_DOCUMENTS_PROVIDER_AUTHORITY =
            "com.android.providers.media.documents";

    private Instrumentation mInstrumentation;
    private Context mContext;
    private UiDevice mDevice;
    private GetResultActivity mActivity;

    private File mFile;
    private Uri mMediaStoreUri;
    private String mTargetPackageName;
    private String mDocumentsUiPackageId;

    @Parameter(0)
    public String mVolumeName;

    @Parameters
    public static Iterable<? extends Object> data() {
        return ProviderTestUtils.getSharedVolumeNames();
    }

    @Before
    public void setUp() throws Exception {
        mInstrumentation = InstrumentationRegistry.getInstrumentation();
        mContext = InstrumentationRegistry.getTargetContext();
        mDevice = UiDevice.getInstance(mInstrumentation);
        final PackageManager pm = mContext.getPackageManager();
        final Intent intent2 = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent2.addCategory(Intent.CATEGORY_OPENABLE);
        intent2.setType("*/*");
        final ResolveInfo ri = pm.resolveActivity(intent2, 0);
        mDocumentsUiPackageId = ri.activityInfo.packageName;

        final Intent intent = new Intent(mContext, GetResultActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        mActivity = (GetResultActivity) mInstrumentation.startActivitySync(intent);
        mInstrumentation.waitForIdleSync();
        mActivity.clearResult();
    }

    @After
    public void tearDown() throws Exception {
        if (mFile != null) {
            mFile.delete();
        }

        if (mActivity != null) {
            final ContentResolver resolver = mActivity.getContentResolver();
            for (UriPermission permission : resolver.getPersistedUriPermissions()) {
                mActivity.revokeUriPermission(
                        permission.getUri(),
                        Intent.FLAG_GRANT_READ_URI_PERMISSION
                            | Intent.FLAG_GRANT_WRITE_URI_PERMISSION);
            }
            mActivity.finish();
        }
    }

    @Test
    public void testGetDocumentUri() throws Exception {
        if (!supportsHardware()) return;

        prepareFile();

        final Uri treeUri = acquireAccess(mFile, Environment.DIRECTORY_DOCUMENTS);
        assertNotNull(treeUri);

        final Uri docUri = MediaStore.getDocumentUri(mActivity, mMediaStoreUri);
        assertNotNull(docUri);

        final ContentResolver resolver = mActivity.getContentResolver();

        // Test reading
        final byte[] expected = "TEST".getBytes();
        final byte[] actual = new byte[4];
        try (ParcelFileDescriptor fd = resolver.openFileDescriptor(docUri, "r")) {
            Os.read(fd.getFileDescriptor(), actual, 0, actual.length);
            assertArrayEquals(expected, actual);
        }

        // Test writing
        try (ParcelFileDescriptor fd = resolver.openFileDescriptor(docUri, "wt")) {
            Os.write(fd.getFileDescriptor(), expected, 0, expected.length);
        }
    }

    @Test
    public void testGetDocumentUri_ThrowsWithoutPermission() throws Exception {
        if (!supportsHardware()) return;

        prepareFile();

        try {
            MediaStore.getDocumentUri(mActivity, mMediaStoreUri);
            fail("Expecting SecurityException.");
        } catch (SecurityException e) {
            // Expected
        }
    }

    @Test
    public void testGetDocumentUri_Symmetry_ExternalStorageProvider() throws Exception {
        if (!supportsHardware()) return;

        prepareFile();

        final Uri treeUri = acquireAccess(mFile, Environment.DIRECTORY_DOCUMENTS);
        Log.v(TAG, "Tree " + treeUri);
        assertNotNull(treeUri);

        final Uri docUri = MediaStore.getDocumentUri(mActivity, mMediaStoreUri);
        Log.v(TAG, "Document " + docUri);
        assertNotNull(docUri);

        final Uri mediaUri = MediaStore.getMediaUri(mActivity, docUri);
        Log.v(TAG, "Media " + mediaUri);
        assertNotNull(mediaUri);

        assertEquals(mMediaStoreUri, mediaUri);
        assertAccessToMediaUri(mediaUri, mFile);
    }

    @Test
    public void testGetMediaUriAccess_MediaDocumentsProvider() throws Exception {
        if (!supportsHardware()) return;

        prepareFile();
        clearDocumentsUi();
        final Intent intent = new Intent();
        intent.setAction(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        mActivity.startActivityForResult(intent, REQUEST_CODE);
        mDevice.waitForIdle();

        findDocument(mFile.getName()).click();
        final Result result = mActivity.getResult();
        final Uri uri = result.data.getData();
        assertEquals(MEDIA_DOCUMENTS_PROVIDER_AUTHORITY, uri.getAuthority());
        final Uri mediaUri = MediaStore.getMediaUri(mActivity, uri);

        assertAccessToMediaUri(mediaUri, mFile);
    }

    private void assertAccessToMediaUri(Uri mediaUri, File file) {
        final String[] projection = {MediaStore.MediaColumns.DISPLAY_NAME};
        try (Cursor c = mContext.getContentResolver().query(
                mediaUri, projection, null, null, null)) {
            assertTrue(c.moveToFirst());
            assertEquals(file.getName(), c.getString(0));
        }
    }

    /**
     * Clears the DocumentsUI package data.
     */
    protected void clearDocumentsUi() throws Exception {
        executeShellCommand("pm clear " + getDocumentsUiPackageId());
    }

    private UiObject findDocument(String label) throws UiObjectNotFoundException {
        final UiSelector docList = new UiSelector().resourceId(getDocumentsUiPackageId()
                + ":id/dir_list");

        // Wait for the first list item to appear
        assertTrue("First list item",
                new UiObject(docList.childSelector(new UiSelector()))
                        .waitForExists(TIMEOUT_MILLIS));

        try {
            //Enforce to set the list mode
            //Because UiScrollable can't reach the real bottom (when WEB_LINKABLE_FILE item)
            // in grid mode when screen landscape mode
            new UiObject(new UiSelector().resourceId(getDocumentsUiPackageId()
                    + ":id/sub_menu_list")).click();
            mDevice.waitForIdle();
        }catch (UiObjectNotFoundException e){
            //do nothing, already be in list mode.
        }

        // Repeat swipe gesture to find our item
        // (UiScrollable#scrollIntoView does not seem to work well with SwipeRefreshLayout)
        UiObject targetObject = new UiObject(docList.childSelector(new UiSelector().text(label)));
        UiObject saveButton = findSaveButton();
        int stepLimit = 10;
        while (stepLimit-- > 0) {
            if (targetObject.exists()) {
                boolean targetObjectFullyVisible = !saveButton.exists()
                        || targetObject.getVisibleBounds().bottom
                        <= saveButton.getVisibleBounds().top;
                if (targetObjectFullyVisible) {
                    break;
                }
            }

            mDevice.swipe(/* startX= */ mDevice.getDisplayWidth() / 2,
                    /* startY= */ mDevice.getDisplayHeight() / 2,
                    /* endX= */ mDevice.getDisplayWidth() / 2,
                    /* endY= */ 0,
                    /* steps= */ 40);
        }
        return targetObject;
    }

    private UiObject findSaveButton() throws UiObjectNotFoundException {
        return new UiObject(new UiSelector().resourceId(
                getDocumentsUiPackageId() + ":id/container_save")
                .childSelector(new UiSelector().resourceId("android:id/button1")));
    }

    private String getDocumentsUiPackageId() {
        return mDocumentsUiPackageId;
    }

    private boolean supportsHardware() {
        final PackageManager pm = mContext.getPackageManager();
        return !pm.hasSystemFeature("android.hardware.type.television")
                && !pm.hasSystemFeature("android.hardware.type.watch");
    }

    public File getVolumePath(String volumeName) {
        return mContext.getSystemService(StorageManager.class)
                .getStorageVolume(MediaStore.Files.getContentUri(volumeName)).getDirectory();
    }

    private void prepareFile() throws Exception {
        final File dir = new File(getVolumePath(mVolumeName),
                Environment.DIRECTORY_DOCUMENTS);
        final File file = new File(dir, "cts" + System.nanoTime() + ".txt");

        mFile = stageFile(R.raw.text, file);
        mMediaStoreUri = MediaStore.scanFile(mContext.getContentResolver(), mFile);

        Log.v(TAG, "Staged " + mFile + " as " + mMediaStoreUri);
    }

    private void assertToolbarTitleEquals(String targetPackageName, String label)
            throws UiObjectNotFoundException {
        final UiSelector toolbarUiSelector = new UiSelector().resourceId(
                targetPackageName + ":id/toolbar");
        final UiSelector titleTextSelector = new UiSelector().className(
                "android.widget.TextView").text(label);
        final UiObject title = new UiObject(toolbarUiSelector.childSelector(titleTextSelector));

        assertTrue(title.waitForExists(TIMEOUT_MILLIS));
    }

    private Uri acquireAccess(File file, String directoryName) throws Exception {
        StorageManager storageManager =
                (StorageManager) mActivity.getSystemService(Context.STORAGE_SERVICE);

        // Request access from DocumentsUI
        final StorageVolume volume = storageManager.getStorageVolume(file);
        final Intent intent = volume.createOpenDocumentTreeIntent();

        // launch the directory directly to avoid unexpected UiObject not found issue
        final Uri rootUri = intent.getParcelableExtra(DocumentsContract.EXTRA_INITIAL_URI);
        final String rootId = DocumentsContract.getRootId(rootUri);
        final String documentId = rootId + ":" + directoryName;
        intent.putExtra(DocumentsContract.EXTRA_INITIAL_URI,
                DocumentsContract.buildDocumentUri(rootUri.getAuthority(), documentId));
        mActivity.startActivityForResult(intent, REQUEST_CODE);

        if (mTargetPackageName == null) {
            mTargetPackageName = getTargetPackageName(mActivity);
        }
        mDevice.waitForIdle();
        assertToolbarTitleEquals(mTargetPackageName, directoryName);

        // Granting the access
        BySelector buttonPanelSelector = By.pkg(mTargetPackageName)
                .res(mTargetPackageName + ":id/container_save");
        mDevice.wait(Until.hasObject(buttonPanelSelector), TIMEOUT_MILLIS);
        final UiObject2 buttonPanel = mDevice.findObject(buttonPanelSelector);
        final UiObject2 allowButton = buttonPanel.findObject(By.res("android:id/button1"));
        allowButton.click();
        mDevice.waitForIdle();

        // Granting the access by click "allow" in confirm dialog
        final BySelector dialogButtonPanelSelector = By.pkg(mTargetPackageName)
                .res(mTargetPackageName + ":id/buttonPanel");
        mDevice.wait(Until.hasObject(dialogButtonPanelSelector), TIMEOUT_MILLIS);
        final UiObject2 positiveButton = mDevice.findObject(dialogButtonPanelSelector)
                .findObject(By.res("android:id/button1"));
        positiveButton.click();
        mDevice.waitForIdle();

        // Check granting result and take persistent permission
        final Result result = mActivity.getResult();
        assertEquals(Activity.RESULT_OK, result.resultCode);

        final Intent resultIntent = result.data;
        final Uri resultUri = resultIntent.getData();
        final int flags = resultIntent.getFlags()
                & (Intent.FLAG_GRANT_READ_URI_PERMISSION
                | Intent.FLAG_GRANT_WRITE_URI_PERMISSION);
        mActivity.getContentResolver().takePersistableUriPermission(resultUri, flags);
        return resultUri;
    }

    private static String getTargetPackageName(Context context) {
        final PackageManager pm = context.getPackageManager();

        final Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        final ResolveInfo ri = pm.resolveActivity(intent, 0);
        return ri.activityInfo.packageName;
    }

    // TODO: replace with ProviderTestUtils
    static String executeShellCommand(String command) throws IOException {
        return executeShellCommand(command,
                InstrumentationRegistry.getInstrumentation().getUiAutomation());
    }

    // TODO: replace with ProviderTestUtils
    static String executeShellCommand(String command, UiAutomation uiAutomation)
            throws IOException {
        Log.v(TAG, "$ " + command);
        ParcelFileDescriptor pfd = uiAutomation.executeShellCommand(command.toString());
        BufferedReader br = null;
        try (InputStream in = new FileInputStream(pfd.getFileDescriptor());) {
            br = new BufferedReader(new InputStreamReader(in, StandardCharsets.UTF_8));
            String str = null;
            StringBuilder out = new StringBuilder();
            while ((str = br.readLine()) != null) {
                Log.v(TAG, "> " + str);
                out.append(str);
            }
            return out.toString();
        } finally {
            if (br != null) {
                br.close();
            }
        }
    }

    // TODO: replace with ProviderTestUtils
    static File stageFile(int resId, File file) throws IOException {
        // The caller may be trying to stage into a location only available to
        // the shell user, so we need to perform the entire copy as the shell
        final Context context = InstrumentationRegistry.getTargetContext();
        UserManager userManager = context.getSystemService(UserManager.class);
        if (userManager.isSystemUser() &&
                 FileUtils.contains(Environment.getStorageDirectory(), file)) {
            executeShellCommand("mkdir -p " + file.getParent());

            try (AssetFileDescriptor afd = context.getResources().openRawResourceFd(resId)) {
                final File source = ParcelFileDescriptor.getFile(afd.getFileDescriptor());
                final long skip = afd.getStartOffset();
                final long count = afd.getLength();

                executeShellCommand(String.format("dd bs=1 if=%s skip=%d count=%d of=%s",
                        source.getAbsolutePath(), skip, count, file.getAbsolutePath()));

                // Force sync to try updating other views
                executeShellCommand("sync");
            }
        } else {
            final File dir = file.getParentFile();
            dir.mkdirs();
            if (!dir.exists()) {
                throw new FileNotFoundException("Failed to create parent for " + file);
            }
            try (InputStream source = context.getResources().openRawResource(resId);
                    OutputStream target = new FileOutputStream(file)) {
                FileUtils.copy(source, target);
            }
        }
        return file;
    }
}
