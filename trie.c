#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie_t {
    bool valid;
    struct trie_t *children[26];
};

typedef struct trie_t *Trie;

Trie init_trie() {
    Trie trie = (Trie)calloc(1, sizeof(struct trie_t));
    return trie;
}

void free_trie(Trie trie) {
    // base case
    if (!trie) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        free_trie(trie->children[i]);
    }
    free(trie);
}

int ord(char c) { return c - 'a'; }

void insert(Trie trie, const char *s) {
    if (*s == '\0') {
        trie->valid = true;
        return;
    }

    // check if s[0] is in the trie
    if (trie->children[ord(*s)] == NULL) {
        trie->children[ord(*s)] = init_trie();
    }
    return insert(trie->children[ord(*s)], s + 1);
}

void print_helper(const Trie trie, char *prefix, int prefix_length) {
    if (!trie) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (trie->children[i]) {
            if (trie->children[i]->valid) {
                prefix[prefix_length] = '\0';
                printf("%s%c\n", prefix, 'a' + i);
            }
            prefix[prefix_length] = 'a' + i;
            print_helper(trie->children[i], prefix,
                         prefix_length + 1);
        }
    }
}

void delete(Trie trie, char *string) {
    if (!trie) {
        return;
    }
    if (*string == '\0') {
        trie->valid = false;
        return;
    }
    delete(trie->children[ord(*string)], string + 1);
}

bool search(Trie trie, char *string) {
    if (!trie) {
        return false;
    }
    if (*string == '\0') {
        return trie->valid;
    }

    return search(trie->children[ord(*string)], string + 1);
}

void print(const Trie trie) {
    char *prefix = (char *)calloc(80, sizeof(char));
    print_helper(trie, prefix, 0);
    free(prefix);
}

// navigate to a node in Trie
Trie navigate(Trie trie, char *prefix) {
    if (!trie) {
        return NULL;
    }
    if (*prefix == '\0') {
        return trie;
    }
    return navigate(trie->children[ord(*prefix)], prefix + 1);
}

// print words with a given prefix
void complete(Trie trie, char *prefix) {
    Trie base = navigate(trie, prefix);
    if (base) {
        print_helper(base, prefix, strlen(prefix));
    }
}

void load_file(Trie trie) {
    FILE *fp = fopen("english.txt", "r");
    int words = 0;
    if (fp) {
        char *string = (char *)calloc(80, sizeof(char));
        while (fscanf(fp, "%s", string) != EOF) {
            insert(trie, string);
            words++;
        }
        free(string);
    }
    printf("%d words scanned\n", words);
    fclose(fp);
}

int main() {
    Trie trie = init_trie();

    load_file(trie);
    while (true) {
        printf(">> trie$ ");

        char *command = (char *)calloc(80, sizeof(char));
        scanf(" %s", command);
        if (!strcmp(command, "insert")) {
            char *string = (char *)calloc(80, sizeof(char));
            scanf(" %s", string);
            insert(trie, string);
            free(string);
        }
        else if (!strcmp(command, "delete")) {
            char *string = (char *)calloc(80, sizeof(char));
            scanf(" %s", string);
            delete (trie, string);
            free(string);
        }
        else if (!strcmp(command, "print")) {
            print(trie);
        }
        else if (!strcmp(command, "exit")) {
            free_trie(trie);
            printf("Bye!\n");
            free(command);
            return 0;
        }
        else if (!strcmp(command, "search")) {
            char *string = (char *)calloc(80, sizeof(char));
            scanf(" %s", string);
            if (search(trie, string)) {
                printf("found!\n");
            }
            else {
                printf("not found\n");
            }
            free(string);
        }
        else if (!strcmp(command, "complete")) {
            char *string = (char *)calloc(80, sizeof(char));
            scanf(" %s", string);
            complete(trie, string);
            free(string);
        }
        free(command);
    }
}
