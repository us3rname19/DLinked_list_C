// 1 вариант.

// Структура содержит фамилию, имя, отчество и 4 оценки по 4-м предметам (массив структур с
// полями предмет, оценка). Удалять из списка имеющих 3 оценки неудовлетворительно. Поиск  
// по фамилии и изменение оценок. Добавлять новые записи в начало списка.

// Задание:

// Разработать программу для создания и работы с двусвязным списком , 
// состоящим из структур. Для работы со списком создать меню со следующими пунктами:

// 1. Создание списка.
// 2. Просмотр списка.
// 3. Добавление в список  новой записи.
// 4. Поиск и корректировка записи в списке.
// 5. Удаление записи из списка.
// 6. Удалить из списка всех имеющих 3 оценки неудовлетворительно.
// 7. Сохранение списка в файле.
// 8. Загрузка списка из файла.
// 9. Выход.

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define n 4


//Объявление структуры предмет\оценка
struct subj {
	char subject[20];
	int mark;
}subj[n];  


//Объявление структуры ФИО
struct info {
	char fname[25]; 
	char mname[25]; 
	char lname[25];
	struct subj St[n]; // Массив структур предмет\оценка
}info;


//Объявление структуры узла
struct spis {
  struct info In;  // Структура с данными
  struct spis *v1; // v1 – указатель на предыдущую структуру
  struct spis *v2; // v2 – указатель на последующую структуру
} spis;
struct spis *head,*tail; // указатели на начало и конец списка


void create(); // создание
void list(struct spis *); // просмотр
void add(struct spis *); // добавление
void search(struct spis *); // Поиск и корректировка
void del(struct spis *); // удаление
void del_u(struct spis *); // удаление имеющих 3 оценки неудовлетворительно.
void save(struct spis *); // Сохранение
void load(void); // Загрузка


// Меню
int main(){ 
char c;
while (1){
    puts("\n1-List creation");
    puts("2-View list");
    puts("3-Add a new data to the list");
    puts("4-Search and repair data in list");
    puts("5-Delete data from the list");
    puts("6-Remove users with bad marks");
    puts("7-Save list in a file");
    puts("8-Load list from file");
    puts("9-Exit\n");
    c=getch();
switch(c){ 
	case '1':create();break;
    case '2':list(head);break;
    case '3':add(tail);break;
    case '4':search(head);break;
    case '5':del(head);break;
    case '6':del_u(head);break;
    case '7':save(head);break;
    case '8':load();break;
    case '9':return 0;
    default : puts("\nError, try again\n");
    }
}
}


// Функция заполнения типовой структуры
struct info input_i(){
struct info *i;
struct info input_i;
i=(struct info *)malloc(1*sizeof(info));
printf("\n Input student name:");
scanf("%s", i->fname); 
printf("\n Input student mname:");
scanf("%s", i->mname);
printf("\n Input student sername:");
scanf("%s", i->lname);
for (int l=0; l<n; l++){
	printf("\n Input subject: ");
	scanf("%s", i->St[l].subject);
	printf("\n Input mark:");
	scanf("%d", &i->St[l].mark);
    }
input_i=*i;
return input_i;
}


// Функция отображения инфо.
void display(struct spis *p){
printf("\nName: %s %s %s \n\n", p->In.fname, p->In.mname, p->In.lname);
for (int i=0; i<n; i++){
	printf("Subject/Mark: %s/%d \n", p->In.St[i].subject, p->In.St[i].mark);
	}
printf("_______________________\n\n");
}


// 1. Функция создание списка
void create(){
struct spis *p,*pred;
pred=NULL;
do {p=(struct spis *)malloc(1*sizeof(spis));
	p->In=input_i(); //Заполнение информацией ФИО структуры/узла         
	p->v1=pred;
	if (pred != NULL) pred->v2=p;
	else head=p;
		 pred=p; 
		 puts("Exit - <esc>");
	}	
while (getch()!=27);
	tail=p;
	tail->v2=NULL;
}


// 2. Функция просмотра списка
void list(struct spis *p){   
if (p==NULL){printf("\nData not found!\n");} // Проверка существования списка
else {
	printf("\n________________________________________________________");
	while (p != NULL){
		display(p);
		p=p->v2;
		}
	printf("________________________________________________________\n");
}
}


// 3. Функция добавления в конец списка
void add(struct spis *p){
if (p==NULL){printf("\nData not found!\n");} // Проверка существования списка
else {
	struct spis *pn;
	pn=(struct spis *)malloc(1*sizeof(spis)); // pn – указатель на новую структуру
	pn->In=input_i(); //Заполнение информацией структуры/узла
	//структура вставляется в конец списка
	pn->v1=tail;
	pn->v2=NULL;
	p->v2=pn;
	tail=pn;
}
}


// 4. Функции поиска и корректировки записи в списке.
// Функция корректировки
void change(struct spis *p){
printf("\nInput replacement data: \n");
p->In=input_i();
}
// Функция поиска
void search(struct spis *p){
int check=0;
char f[25]; // – Строка для искомой фамилии
printf("Input Name/Mname/Sername for search: ");
scanf("%s",f);
while (p!=NULL){
  if (strcmp((p->In.fname),f)==0){display(p);check=1;change(p);}  // если найдена заданное имя
  if (strcmp((p->In.mname),f)==0){display(p);check=1;change(p);}  // если найдена заданное отчество
  if (strcmp((p->In.lname),f)==0){display(p);check=1;change(p);}  // если найдена заданная фамилия
  p=p->v2;
  }
if (check!=1){printf("\nData not found!\n");}
}


// 5. Удаление записи из списка.
// Функция удаления
void deleting(struct spis *p){
struct spis *temp;
if (p==head){ // если найденная запись - первая
	head=p->v2;
	head->v1=NULL;
	free(p);
	p=head;
	}
else if (p==tail){ // если найденная запись - последняя 
	tail=p->v1;
	tail->v2=NULL;
	free(p);
	p=tail;
	}
else{ // удаление из средины списка 
	p->v2->v1=p->v1;
	p->v1->v2=p->v2;
	temp=p;
	p=p->v2;
	free(temp);
	}
}
// Запрос на удаление
void del(struct spis *p){
int check=0;
char f[20]; // – Строка для удаляемой фамилии
printf("Input Name/Mname/Sername to delete: ");
scanf("%s",f);
p=head;
while (p!=NULL){
	if (strcmp((p->In.fname),f)==0){deleting(p);check=1;}  // если найдена заданное имя
    if (strcmp((p->In.mname),f)==0){deleting(p);check=1;}  // если найдена заданное отчество
    if (strcmp((p->In.lname),f)==0){deleting(p);check=1;}  // если найдена заданная фамилия 
    p=p->v2; // если заданная фамилия не найдена – продвигаемся по списку
    }
if (check!=1){printf("\nData not found!\n");}
}


// 6. Удалить из списка всех имеющих 3 оценки неудовлетворительно.
void del_u(struct spis *p){
if (p==NULL){printf("\nData not found!\n");} // Проверка существования списка
else {
	int check=0;
	p=head;
	while (p!=NULL){
		int sum=0;
		for (int i=0; i<n; i++){sum+=p->In.St[i].mark;}
		if (sum<=10){ // Удаление всех у кого оценок в сумме <= 10
			printf("\nUser %s %s %s was deleted\n", p->In.fname, p->In.mname, p->In.lname);
			deleting(p);check=1;}
		p=p->v2;
		}
	if (check!=1){printf("\nData not found!\n");}
}
}


// 7. Сохранение списка в файле.
void save(struct spis *p){
FILE *tf;
tf=fopen("file.dat","wb"); // открытие бинарного файла для записи
p=head;
struct info A;
if (p!=NULL){
	printf("\n<Saving...>\n\n");
	while (p!=NULL){
		A=p->In;
		fwrite(&A,sizeof(A)+1,1,tf); // запись в файл структуры
		printf(" %s %s %s - Saved.\n", A.fname, A.mname, A.lname);
		p=p->v2;
		}	
	printf("\n<!Done.>\n"); 
    }
else {printf("\nData not found!\n");}
fclose(tf); 
}


// 8. Загрузка списка из файла.
void load(){
FILE *tf;
struct info A;
tf=fopen("file.dat","rb"); // открытие бинарного файла для чтения
if (tf==NULL){printf("\nData not found!\n");}  //Проверка на существование файла или ошибку чтения
else{
	struct spis *p,*pred;
    pred=NULL;
	printf("\n<Loading...>\n\n");
	while (fread(&A,sizeof(A)+1,1,tf)){ // чтение из файла структуры
		do {p=(struct spis *)malloc(1*sizeof(spis));
           	p->In=A; //Заполнение информацией структуры/узла          
	        p->v1=pred;
	        if (pred != NULL) pred->v2=p;
	        else head=p;
		         pred=p; 
		         break;
	        }	
        while (getch()!=27);
               tail=p;
	           tail->v2=NULL;
	    printf(" %s %s %s - loaded\n", A.fname, A.mname, A.lname);
    //printf("\n<!Done.>\n");   
    }
    } 
fclose(tf); 
}




