/*
    this is >>>GAME FILE<<<
    this file will contains
    field manager, get input, get set subjects,
    player manager
*/

#ifndef GAME_H
#define GAME_H

// subject
const char *subjects[] = {
    "hana",
    "kusa",
    "wara",
    "konnnitiwa",
    "arigatou",
    "sayounara",
    "sumimasen",
    "ohayou",
    "konnbannha",
    "oyasumi",
    "itadakimasu",
    "gotisousama",
    "douitasimasite",
    "otukaresama",
    "gomennnasai",
    "iie",
    "hai",
    "uresii",
    "sugoi",
    "bikkuri",
    "okaeri",
    "omedetou"
};
// current subject
int cs = 0;
int lastcs = 0;

// player
int input;
int lastInput;
char inputAlpha;
int charactor;
int charactorSize;

void playerInOut(int input);

void drawBoard();

void drawSqare(int row, int col);

void setSubjects();
#endif