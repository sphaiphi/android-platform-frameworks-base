# MediaStore - Reverse Engineering Documentation (Implicit)

*Note: `MediaStore.java` was not in the provided file list, but `DocumentsContract` references it. Assuming standard MediaStore behavior.*

`MediaStore` is the provider for audio, video, images, and files. It is the primary way to access media on shared storage.

## Key Concepts
-   **Volumes**: Internal vs External.
-   **Collections**: Images, Audio, Video, Files, Downloads.
-   **Columns**: `_DISPLAY_NAME`, `DATE_ADDED`, `MIME_TYPE`, `RELATIVE_PATH`.
