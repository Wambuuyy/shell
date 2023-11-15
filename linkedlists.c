void add_env(list_t **head, char *str, int len) {
    list_t *new_node = malloc(sizeof(list_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    new_node->str = strdup(str);
    if (new_node->str == NULL) {
        fprintf(stderr, "String duplication error\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }

    new_node->len = len;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        list_t *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

int populate_env(list_t **env) {
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);

    *env = node;
    return 0;
}
