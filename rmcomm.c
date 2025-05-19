int rmcomm(int argc, char *argv[]) {
    FILE *in = fopen(argv[0], "r");
    FILE *out = fopen(argv[1], "w");
    int output[2];
    int commcount = 0;
    char riga[1024];
    int comm = 0;
    while (fgets(riga, 1024, in)) {
        int len = strlen(riga);
        int i = 0;
        int rigacomm = 0;
        char *var = strtok(riga, " \t\n");
        while (i < len) {
            if (comm) {
                //Cerca la fine di un commento
                if (i + 1 < len && riga[i] == '*' && riga[i + 1] == '/') {
                    comm = 0;
                    i += 2; //Salta '/*'
                } else {
                    rigacomm= 1;
                    i++;
                }
            } else {
                //Cerca l'inizio di un commento
                if (i + 1 < len && riga[i] == '/' && riga[i + 1] == '*') {
                    comm = 1;
                    rigacomm = 1;
                    i += 2; //Salta '*/'
                } else if (i + 1 < len && riga[i] == '/' && riga[i + 1] == '/') {
                    rigacomm = 1;
                    break; //Commento su una riga, salta il resto della riga
                } else {
                    if (riga[i] != '\n') {
                        fprintf(out, "%c", riga[i]); //Stampa il carattere solo se non è newline
                    }
                    i++;
                }
            }
        }
        if (!comm && riga[len-1] == '\n'){
            fprintf(out, "\n"); //Stampa un newline se non siamo in un commento a più righe
        }
        if (rigacomm) {
            commcount++; //Conta righe di commenti eliminate
        }
    }
    fclose(in);
    fclose(out);
    return commcount;
}
