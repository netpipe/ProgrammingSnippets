https://stackoverflow.com/questions/1519885/defining-own-main-functions-arguments-argc-and-argv

int my_main() {
    char  arg0[] = "programName";
    char  arg1[] = "arg";
    char  arg2[] = "another arg";
    char* argv[] = { &arg0[0], &arg1[0], &arg2[0], NULL };
    int   argc   = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

    QApplication the_application(argc, &argv[0]);
    return the_application.run();
}
