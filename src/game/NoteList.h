
e_moment_type {
    NoteChanged;
    TempoChanged;

    Section;    // Solos,…
};

class moment {
    int time;   //milliseconds ?

    e_moment_type type;

    // 0 : no changes
    // 1 : NoteON
    // -1: NoteOff
    bool notesChanged[5];
    // Ho/Po note
    bool needPick;


};
