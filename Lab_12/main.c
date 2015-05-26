#define _CRT_SECURE_NO_WARNINGS

/* ЛАБОРАТОРНАЯ РАБОТА 12. УКАЗАТЕЛИ.ДИНАМИЧЕСКИЕ СТРУКТУРЫ ДАННЫХ.ОБРАБОТКА ДВУХСВЯЗНЫХ СПИСКОВ
*
* ЗАДАНИЕ
* Вводится строка из строчных латинских букв, слова разделены пробелами, признак конца ввода - точка.
* При выполнении задания предложение организовать в виде двухсвязного списка слов.
* Программа должна содержать функции формирования исходного списка,
* вывода списка до и после модификации и реализации непосредственно варианта задания.
*
* 27 вариант
* Перед N-ым элементом списка вставить новое заданное слово.
*
* Выполнил Юрьев Георгий, группа ПМ-13
*/

#include <stdio.h>
#include <string.h>

#define MAX_SENTENCE_ARRAY_LENGTH 255
#define MAX_WORD_ARRAY_LENGTH 20

struct sentence {
	char word[MAX_WORD_ARRAY_LENGTH];
	struct list *next;
	struct list *prev;
};
typedef struct sentence* list;

typedef struct DblLinkedList {
	size_t size;
	list head;
	list tail;
} DblLinkedList;


DblLinkedList* createDblLinkedList();
void input(DblLinkedList**);
void output(DblLinkedList*);
void insertBeforeNth(DblLinkedList**);

int main() {
	DblLinkedList *head = createDblLinkedList();
	input(&head);
	output(head);
	insertBeforeNth(&head);
	output(head);
	system("PAUSE");
	return 0;
}

DblLinkedList* createDblLinkedList() {
	DblLinkedList *tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;
	return tmp;
}

void input(DblLinkedList **dblist) {
	int i; // для счетчика внутри массива символов для слова (wrd[])
	char *cur, sntnc[MAX_SENTENCE_ARRAY_LENGTH];
	list current = NULL;
	puts("Enter the sentence with the dot in the end.");
	gets(sntnc);

	for (cur = sntnc, i = 0; *cur != '.'; cur++, i++) { // обход каждого символа в строке
		if (*cur == '\0') { // если предложение завершилось некорректно
			system("cls");
			puts("Warning! The sentence should have a dot in the end.");
			break;
		}
		else {
			if (*cur != ' ') { // если встречен символ отличный от пробела
				if (current == NULL) { // если это новое слово, выделим память и подготовим счетчик
					if ((current = (list)malloc(sizeof(struct sentence))) == NULL) {
						puts("Can not allocate memory!");
						break;
					}
					i = 0;
				}
				current->word[i] = *cur;
				if ((*(cur + 1) == ' ') || (*(cur + 1) == '.') || (*(cur + 1) == '\0')) { // если слово закончилось
					// дописываем нулевой символ в конец слова и переходим к передаче слова в список 
					current->word[++i] = '\0';
					if ((*dblist)->size == 0) { // если список пуст
						(*dblist)->head = (*dblist)->tail = current;
						current->next = current->prev = NULL;
					}
					else { // добавляем элемент в уже существующий список в конец
						current->next = NULL;
						current->prev = (*dblist)->tail;
						(*dblist)->tail->next = current;
						(*dblist)->tail = current;
					}
					(*dblist)->size++;
					current = NULL;
				}
			}
		}
	}
}

void output(DblLinkedList *dblist) {
	list current = NULL;
	if (dblist->head == NULL) {
		puts("List doesn't exist!");
	}
	else {
		printf("\nThere are %d words in the sentence:\n", dblist->size);
		for (current = dblist->head; current != NULL; current = current->next) {
			puts(current->word);
		}
	}
}

void insertBeforeNth(DblLinkedList **dblist) {
	list current = NULL, temp = NULL;
	int i, pos = 0;
	if ((*dblist)->head == NULL) {
		puts("List doesn't exist!");
	}
	else {
		if (((current = (list)malloc(sizeof(struct sentence))) == NULL) || ((temp = (list)malloc(sizeof(struct sentence))) == NULL)) {
			puts("Can not allocate memory!");
			return;
		}
		do {
			puts("\nEnter the WORD and the NUMBER\nof the position before which you want to insert the word THROUGH THE GAP");
			fflush(stdin);
		} while ((scanf("%s %d", temp->word, &pos) != 2) || (pos <= 0) || (pos > (*dblist)->size));
		for (i = 1, current = (*dblist)->head; i < pos; i++, current = current->next)
			;
		if (current->prev == NULL) {
			(*dblist)->head = temp;
			temp->prev = NULL;
			temp->next = current;
			current->prev = temp;
		}
		else {
			temp->next = current;
			temp->prev = current->prev;

			current = current->prev;
			current->next = temp;

			current = temp->next;
			current->prev = temp;
		}
		(*dblist)->size++;
	}
}
