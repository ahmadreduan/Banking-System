
    struct stat st = {0};
    if (stat("userdata", &st) == -1 && mkdir("userdata", 0700) != 0)
    {
        perror("Error creating userdata directory");
        return;
    }
    char first_name[50], last_name[50];
