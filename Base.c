#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int pageNumber;
    bool dirty;
    int lastUsed;
} PageFrame;

typedef struct PageFrameNode {
    PageFrame frame;
    struct PageFrameNode* next;
} PageFrameNode;

typedef struct {
    int pageNumber;
    char operation;
} TraceEntry;

int read_trace_file(char *filename, TraceEntry **traceEntries) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    int traceLength = 0;
    int capacity = 10;
    *traceEntries = malloc(capacity * sizeof(TraceEntry));

    while (fscanf(file, "%d %c", &((*traceEntries)[traceLength].pageNumber), &((*traceEntries)[traceLength].operation)) == 2) {
        traceLength++;

        if (traceLength >= capacity) {
            capacity *= 2;
            *traceEntries = realloc(*traceEntries, capacity * sizeof(TraceEntry));
        }
    }

    fclose(file);
    return traceLength;
}

PageFrameNode* create_frame_list(int nFrames) {
    PageFrameNode* head = NULL;
    PageFrameNode* current = NULL;

    for (int i = 0; i < nFrames; i++) {
        PageFrameNode* new_node = malloc(sizeof(PageFrameNode));
        new_node->frame.pageNumber = -1;
        new_node->frame.dirty = false;
        new_node->frame.lastUsed = -1;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            current = head;
        } else {
            current->next = new_node;
            current = current->next;
        }
    }

    return head;
}

void free_frame_list(PageFrameNode* head) {
    PageFrameNode* temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void fifo_algorithm(TraceEntry *traceEntries, int traceLength, int nFrames) {
    PageFrameNode* frames = create_frame_list(nFrames);
    PageFrameNode* current = frames;
    int frameIndex = 0;
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

    printf("Contents of page frames:\n");
    current = frames;
    while (current != NULL) {
        printf("%d ", current->frame.pageNumber);
        current = current->next;
    }
    printf("\nNumber of Reads: %d\n", reads);
    printf("Number of Writes: %d\n", writes);

    free_frame_list(frames);
}

void lru_algorithm(TraceEntry *traceEntries, int traceLength, int nFrames) {
    PageFrameNode* frames = create_frame_list(nFrames);
    int reads = 0, writes = 0;
    PageFrameNode* current;

    for (int i = 0; i < traceLength; i++) {
        bool found = false;
        current = frames;
        for (int j = 0; j < nFrames; j++) {
            if (current->frame.pageNumber == traceEntries[i].pageNumber) {
                current->frame.dirty |= (traceEntries[i].operation == 'W');
                current->frame.lastUsed = i;
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            PageFrameNode* minNode = frames;
            current = frames->next;
            for (int j = 1; j < nFrames; j++) {
                if (current->frame.lastUsed < minNode->frame.lastUsed) {
                    minNode = current;
                }
                current = current->next;
            }

            if (minNode->frame.dirty) {
                writes++;
            } else {
                reads++;
            }

            minNode->frame.pageNumber = traceEntries[i].pageNumber;
            minNode->frame.dirty = (traceEntries[i].operation == 'W');
            minNode->frame.lastUsed = i;
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
}

int main() {
    TraceEntry *traceEntries;
    int traceLength = read_trace_file("trace.txt", &traceEntries);

    printf("FIFO Algorithm:\n");
    fifo_algorithm(traceEntries, traceLength, 3);

    printf("\nLRU Algorithm:\n");
    lru_algorithm(traceEntries, traceLength, 3);

    free(traceEntries);
    return 0;
}
