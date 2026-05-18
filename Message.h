#ifndef MESSAGE_H
#define MESSAGE_H

struct Message {
    int id;               
    int type;             
    char text[100];       
    int priority;         
};

inline void customStrCpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < 99) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

#endif