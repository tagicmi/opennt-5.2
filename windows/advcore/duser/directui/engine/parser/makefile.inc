# Parser generation
# for flex: -S$(_NTDRIVE)$(_NTROOT)\tools\flex.skl, gen: $(_NTDRIVE)$(_NTROOT)\tools\flex -B -L -oScan.cpp scan.l

gen:
    set bison_simple=$(_NTDRIVE)$(_NTROOT)\tools\Bison.skl 
    bison -l -oParse.cpp -d parse.y
