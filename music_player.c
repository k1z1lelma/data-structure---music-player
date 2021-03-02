#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//*************************
// YORUMLARIM
//*************************
/*
Bu uygulamayi gerceklestirirken doubly linkedlist veri yapisini kullandim.
Bu yapiyi kullanmamdaki en büyük ozellik node lar arasýnda cift yonlu ilerleyebilmekti.
Neden array yapisi yerine bir linkedlist yapýsý kullandýgýmýn sebebi ise bir sarkiyi bir
elemandan once veya sonrasina tasiyabilmek icin veya silme gibi diger islemleri de gerceklestirebilmek
icin hem verinin hem de adresinin tutuldugu bir yapiya ihtiyacim vardi.hemde listedeki sarki listeler
sayi siniri bulunmadigi icin de linkedlist yapisini tercih ettim.arasinda cift yonlu
dolasabilmek icinde doubly linkedlidt kullanmayý tercih ettim. ornegin listenin sonuna geldigimizde bir
sonraki sarkýyý calmak icin hata vermemesi icin head deki sarkiyi caliyor ya da en bastaki sarki ise de bu sefer
en sondaki sarkiyi caliyor.
*/

//******************************
// NODE VE OZELLIKLERI
//******************************
struct node
{
    char song[50];
    struct node *previous;
    struct node *next;
};

// doubly linkedlistin headini tanimladik
struct node *dll_head;


//*********************************************************
//    I/O ISLEMLERI ICIN GEREKLI DEGISKENLER
//*********************************************************
FILE* file_in, *file_out;

int buffer;
char order[50], location_tab;

char new_song_name[50], first_last;
char after_before, tasinacak[50], referans[50];
char silinecek[50];
char play_after_before;
char bastan_sona_sondan_basa;

int location;

char playing_song[50];

int sayac = 0;


char reverse_element[50];

//************************************
//        GEREKLI FONKSIYONLAR
//************************************


//**********************
// INSERT SONG
//**********************

void push_dll_begin()
{
    struct node *dll;
    dll = (struct node *)malloc(sizeof(struct node));

    if (dll_head == NULL)
    {
        dll->next = NULL;
        dll->previous = NULL;
        strcpy(dll->song, new_song_name);
        dll_head = dll;
    }
    else
    {
        strcpy(dll->song, new_song_name);
        dll->previous = NULL;
        dll->next = dll_head;
        dll_head->previous = dll;
        dll_head = dll;
    }

}

//**************************************

void push_dll_last()
{
    struct node *dll,*temp;

    dll = (struct node *) malloc(sizeof(struct node));

    strcpy(dll->song, new_song_name);
    if (dll_head == NULL)
    {
        dll->next = NULL;
        dll->previous = NULL;
        dll_head = dll;
    }
    else
    {
        temp = dll_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = dll;
        dll->previous = temp;
        dll->next = NULL;
    }
}

//******************
// MOVE SONG KOMUTU
//******************

void move_song_pre()
{
    struct node *dll, *tmp;
    tmp = dll_head;
    dll = dll_head;
    while (tmp->song != tasinacak)
    {
        if (strcmp(tmp->song, tasinacak) == 0)
        {
            break;
        }
        tmp = tmp->next;
    }
    tmp->previous->next = tmp->next;
    tmp->next->previous = tmp->previous;
    while (dll->song != referans)
    {
        if (strcmp(dll->song, referans) == 0)
        {
            break;
        }
        dll = dll->next;
    }
    strcpy(tmp->song, tasinacak);
    tmp->previous = dll->previous;
    dll->previous->next = tmp;
    tmp->next = dll;
    dll->previous = tmp;
}


void move_song_next()
{
    struct node *dll, *tmp;
    tmp = dll_head;
    dll = dll_head;
    while (tmp->song != tasinacak)
    {
        if (strcmp(tmp->song, tasinacak) == 0)
        {
            break;
        }
        tmp = tmp->next;
    }
    tmp->previous->next = tmp->next;
    tmp->next->previous = tmp->previous;
    while (dll->song != referans)
    {
        if (strcmp(dll->song, referans) == 0)
        {
            break;
        }
        dll = dll->next;
    }
    strcpy(tmp->song, tasinacak);
    tmp->previous = dll;
    dll->next->previous = tmp;
    tmp->next = dll->next;
    dll->next = tmp;

}


//**************
// PLAY SONG
//**************

void order_playing_song()
{
    if (play_after_before == 'N')
    {
        strcpy(playing_song, dll_head->song);
        fprintf(file_out, "Playing\t%s\n", playing_song);
        fprintf(file_out, "%s\n", "*****");
        //printf("Playing\t%s\n", playing_song);
        //printf("*****\n");
    }
    else
    {
        struct node *tmp;
        tmp = dll_head;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        strcpy(playing_song, tmp->song);
        fprintf(file_out, "Playing\t%s\n", playing_song);
        fprintf(file_out, "%s\n", "*****");
        //printf("Playing\t%s\n", playing_song);
        //printf("*****\n");
    }
}

//********************
// REMOVE SONG
//********************

void delete_song()
{
    struct node *dll;
    dll = dll_head;
    while (dll->song != silinecek)
    {
        if (strcmp(dll->song, silinecek) == 0)
        {
            break;
        }
        dll = dll->next;
    }

    int sil = sizeof_list(dll);
    if (sil == 1)
    {
        dll_head = NULL;
    }
    else if (strcmp(dll_head->song,silinecek) == 0)
    {
        dll->next->previous = NULL;
        dll_head = dll->next;
    }
    else if (dll->next == NULL)
    {
        dll->previous->next = NULL;
        dll_head->previous = dll->previous;

    }
    else if (dll->next->next == NULL)
    {
        dll->next = NULL;
    }
    else if (dll->previous == NULL)
    {
        dll->next->previous = NULL;
    }
    else
    {
        dll->previous->next = dll->next;
        dll->next->previous = dll->previous;
    }


}

//******************
// BAZI YARDIMCILAR
//******************


int sizeof_list()
{
    int size = 0;
    struct node *link;

    if (dll_head == NULL)
    {
        return size;
    }

    link = dll_head;
    while (link != NULL)
    {
        link = link->next;
        size++;
    }
    return size;
}


//*********************
// REVERSE PLAYLIST
//*********************

//*********************
// REVERSE YARDIMCI
//*********************
void for_reverse_delete()
{
    struct node *dll;
    dll = dll_head;
    while (dll->song != reverse_element)
    {
        if (strcmp(dll->song, reverse_element) == 0)
        {
            break;
        }
        dll = dll->next;
    }


    if (dll->next == NULL)
    {
        dll->previous->next = NULL;
        dll_head->previous = dll->previous;

    }
    else if (dll->next->next == NULL)
    {
        dll->next = NULL;
    }
    else if (dll->previous == NULL)
    {
        dll->next->previous = NULL;
    }
    else
    {
        dll->previous->next = dll->next;
        dll->next->previous = dll->previous;
    }


}

void for_reverse_push()
{
    struct node *dll;
    dll = (struct node *)malloc(sizeof(struct node));


    if (dll_head == NULL)
    {
        dll->next = NULL;
        dll->previous = NULL;
        strcpy(dll->song, reverse_element);
        dll_head = dll;
    }
    else
    {
        strcpy(dll->song, reverse_element);
        dll->previous = NULL;
        dll->next = dll_head;
        dll_head->previous = dll;
        dll_head = dll;
    }

}

//*************
// REVERSE
//*************
void reverse()
{
    struct node *dll;
    struct node *rev;

    dll = dll_head;


    while (dll != NULL)
    {
        strcpy(reverse_element, dll->song);

        for_reverse_push();
        dll = dll->next;
    }

    int size = sizeof_list();
    int stop = size / 2;

    rev = dll_head;
    while (size >= stop + 1)
    {
        if (size == stop + 1)
        {
            rev->next = NULL;
        }
        rev = rev->next;
        size = size - 1;
    }

}


//***********************
// PRINT PLAYLIST
//***********************

void print_output_playlist()
{
    struct node *dll;

    dll = dll_head;

    if (dll_head == NULL)
    {
        fprintf(file_out, "%s\n", "No Songs To Print");
        fprintf(file_out, "%s\n", "*****");
        //printf("%s\n", "No Songs To Print");
        //printf("%s\n", "*****");

    }
    else
    {

        while (dll != NULL)
        {
            fprintf(file_out, "%s\n", dll->song);
            //printf("%s\n", dll->song);
            dll = dll->next;
        }
        fprintf(file_out, "%s\n", "*****");
        //printf("%s\n", "*****");
    }

}


void print_output_playlist_reverse()
{
    reverse();
    print_output_playlist();
    reverse();
}


//*********************************
// MAIN FONKSIYONU
//*********************************

int
main()
{
    file_in = fopen("input.txt", "r");
    file_out = fopen("output.txt", "w");
    buffer = fscanf(file_in, "%s", &order);

    strcpy(playing_song, order);

    while (buffer == 1)
    {

        fscanf(file_in, "%c\t", &location_tab);

        if (strcmp("InsertSong", order) == 0)
        {
            fscanf(file_in, "%c\t%s", &first_last, &new_song_name);
            if (first_last == 'H')
            {
                push_dll_begin();
            }
            else
            {
                push_dll_last();
            }
        }

        else if (strcmp("MoveSong", order) == 0)
        {
            fscanf(file_in, "%c\t%s\t%s", &after_before, &tasinacak, &referans);
            if (after_before == 'B')
            {
                move_song_pre();

            }
            else
            {
                move_song_next();
            }


        }
        else if (strcmp("RemoveSong", order) == 0)
        {

            fscanf(file_in, "%s", &silinecek);

            if (strcmp(playing_song, silinecek) == 0)
            {
                fprintf(file_out, "%s\n", "Cannot Remove The Playing Song");
                fprintf(file_out, "%s\n", "*****");
                //printf("%s\n", "Cannot Remove The Playing Song");
                //printf("%s\n", "*****");
            }

            else
            {

                delete_song();
            }

        }



        else if (strcmp("PlaySong", order) == 0)
        {
            fscanf(file_in, "%c", &play_after_before);

            if (dll_head == NULL)
            {
                fprintf(file_out, "%s\n", "No Songs To Play");
                fprintf(file_out, "%s\n", "*****");
                //printf("%s\n", "No Songs To Play");
                //printf("%s\n", "*****");

            }
            else if (strcmp("PlaySong", playing_song) == 0)
            {
                order_playing_song(); ;
            }
            else if (strcmp("InsertSong", playing_song) == 0)
            {
                order_playing_song();
            }
            else if (strcmp("ReversePlaylist", playing_song) == 0)
            {
                order_playing_song();
            }
            else if (strcmp("MoveSong", playing_song) == 0)
            {
                order_playing_song(); ;
            }
            else if (strcmp("RemoveSong", playing_song) == 0)
            {
                order_playing_song();
            }
            else if (strcmp("PrintPlaylist", playing_song) == 0)
            {
                order_playing_song();
            }
            else
            {
                struct node *tmp;
                tmp = dll_head;
                while (tmp->song != playing_song)
                {
                    if (strcmp(tmp->song, playing_song) == 0)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if (play_after_before == 'N')
                {
                    if (tmp->next == NULL)
                    {
                        strcpy(playing_song, dll_head->song);
                        fprintf(file_out, "Playing\t%s\n", playing_song);
                        fprintf(file_out, "%s\n", "*****");
                        //printf("Playing\t%s\n", playing_song);
                        //printf("*****\n");
                    }
                    else
                    {
                        strcpy(playing_song, tmp->next->song);
                        fprintf(file_out, "Playing\t%s\n", playing_song);
                        fprintf(file_out, "%s\n", "*****");
                        //printf("Playing\t%s\n", playing_song);
                        //printf("*****\n");
                    }
                }
                else
                {
                    if (tmp->previous == NULL)
                    {
                        struct node *temp;
                        temp = dll_head;
                        while (temp->next != NULL)
                        {
                            temp = temp->next;
                        }
                        strcpy(playing_song, temp->song);
                        fprintf(file_out, "Playing\t%s\n", playing_song);
                        fprintf(file_out, "%s\n", "*****");
                        //printf("Playing\t%s\n", playing_song);
                        //printf("*****\n");
                    }
                    else
                    {
                        strcpy(playing_song, tmp->previous->song);
                        fprintf(file_out, "Playing\t%s\n", playing_song);
                        fprintf(file_out, "%s\n", "*****");
                        //printf("Playing\t%s\n", playing_song);
                        //printf("*****\n");
                    }
                }

            }

        }

        else if (strcmp("PrintPlaylist", order) == 0)
        {
            fscanf(file_in, "%c", &bastan_sona_sondan_basa);

            if (bastan_sona_sondan_basa == 'F')
            {
                print_output_playlist();
            }
            else
            {
                print_output_playlist_reverse();

            }


        }
        else if (strcmp("ReversePlaylist", order) == 0)
        {
            reverse();

        }
        else
        {
            break;
        }
        buffer = fscanf(file_in, "%s", order);

    }
    fclose(file_in);
    fclose(file_out);
}
