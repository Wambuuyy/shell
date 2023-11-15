int shell(int *info, char **av) {
    ssize_t input_result = 0;
    int builtin_result = 0;

    while (input_result != -1 && builtin_result != -2) {
        clear_info(info);

        if (is_interactive(info))
            printf("$ ");

        putchar(BUF_FLUSH);

        input_result = read_input(info);

        if (input_result != -1) {
            set_info(info, av);
            builtin_result = identify_builtin(info);
            if (builtin_result == -1)
                identify_command(info);
        } else if (is_interactive(info))
            putchar('\n');

        release_info(info, 0);
    }

    store_history(info);
    release_info(info, 1);

    if (!is_interactive(info) && info[1])  // Assuming info[1] contains the status
        exit(info[1]);

    if (builtin_result == -2) {
        if (info[2] == -1)  // Assuming info[2] contains err_num
            exit(info[1]);
        exit(info[2]);
    }

    return builtin_result;
}
