
    PageFrameNode* frames = create_frame_list(nFrames);
    PageFrameNode* current = frames;
    int reads = 0, writes = 0;

    for (int i = 0; i < traceLength; i++) {
        bool found = false;
        current = frames;
        for (int j = 0; j < nFrames; j++) {
            if (current->frame.pageNumber == traceEntries[i].pageNumber) {
                current->frame.dirty |= (traceEntries[i].operation == 'W');
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            current = frames;
            for (int j = 0; j < frameIndex; j++) {
                current = current->next;
            }

            if (traceEntries[i].operation == 'W') {
                current->frame.dirty = true;
            } else {
                current->frame.dirty = false;
            }

            if (current->frame.dirty) {
                writes++;
            } else {
                reads++;
            }

            current->frame.pageNumber = traceEntries[i].pageNumber;
            frameIndex = (frameIndex + 1) % nFrames;
        }
    }

    printf("Contents of page frames:\n");
    current = frames;
    while (current != NULL) {
        printf("%d ", current->frame.pageNumber);
        current = current->next;
    }
    printf("\nNumber of Reads: %d\n", reads);
    printf("Number of Writes: %d\n", writes);

    free_frame_list(frames);