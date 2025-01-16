$(O)\embedded.mst : themes.ini Default\Default.ini
    packthem /o $(O)\embedded.mst /k .
     $(BINPLACE_CMD)
