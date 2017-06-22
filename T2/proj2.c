#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/slab.h>

#define SIZE 5




// estrutura que corresponde a um item da hashtable
struct DataItem {
   char* value;
   int lifeuntil;
   int key;
};




// ---------------------------------
// inicio da declaracao de variaveis
int i;
int j;
char* kvalue;
char atual;
int klifeuntil;

int hashIndex;

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

struct DataItem* removido;
struct DataItem* pesquisado;

int count;
// fim da declaracao de variaveis
// ------------------------------




// -------------------------------
// inicio da declaracao de funcoes


// devolve o valor hash baseado na chave a ser inserida
int hashCode(int key) {
   return key % SIZE;
}




// procura um item com a chave key
struct DataItem *search(int key) {
   hashIndex = hashCode(key);  
	
   while(hashArray[hashIndex] != NULL) {
      if(hashArray[hashIndex]->key == key){
         return hashArray[hashIndex];
      }

      ++hashIndex;
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}




// insere um item com chave key, string value e vida maxima lifeuntil
// caso nao haja nenhuma posicao disponivel nada eh inserido e retorna 0
// retorna 1 em caso de sucesso
int insert(int key, char* value, int lifeuntil) {

   item = (struct DataItem*) kmalloc(sizeof(struct DataItem), GFP_KERNEL);
   item->value = value;
   item->lifeuntil = lifeuntil;
   item->key = key;

   hashIndex = hashCode(key);

   count = 0;
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      count++;
      if(count > SIZE){
        return(0);
      }

      ++hashIndex;
      hashIndex %= SIZE;
   }

   hashArray[hashIndex] = item;

   return(1);
}




// remove e devolve um item com chave key
// caso nao haja sera devolvido NULL
struct DataItem* delete(int key) {

   hashIndex = hashCode(key);

   count = 0;
   while(hashArray[hashIndex] != NULL) {
      count++;
      if(count > SIZE){
        return(0);
      }

      if(hashArray[hashIndex]->key == key) {
         struct DataItem* temp = hashArray[hashIndex]; 
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
      ++hashIndex;
      hashIndex %= SIZE;
   }   

   return NULL;        
}




asmlinkage long sys_settmpkey(int key, char* value, unsigned int lifespan){

  klifeuntil = (jiffies / HZ) + lifespan;

  i = 0;
  atual = value[i];
  while(atual != '\0'){
    i++;
    atual = value[i];
  }
  i++;

  kvalue = (char*) kmalloc(i * sizeof (char), GFP_KERNEL);
  for(j = 0; j < i; j++){
    kvalue[j] = value[j];
  }

  pesquisado = search(key);

  if(pesquisado == NULL){
       return(insert(key, kvalue, klifeuntil));
  }else{
     if(pesquisado->key == -1){
       return(insert(key, kvalue, klifeuntil));
     }
  }

  return(0);
}




asmlinkage long sys_gettmpkey(int key, int n, char* value){

  removido = delete(key);

  if(removido != NULL){

	if((jiffies / HZ) > removido->lifeuntil){
		return(0);
	}

	i = 0;
	atual = removido->value[i];

	while(atual != '\0'){
		i++;
		atual = removido->value[i];
	}
	i++;

	for(j = 0; j < i; j++){
		value[j] = removido->value[j];
	}

	return (1);
  }

  return(0);
}


// fim da declaracao de funcoes
// ----------------------------

