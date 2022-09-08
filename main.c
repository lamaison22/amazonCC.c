#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _product{
    int code;
    char name[30];
    float price;
    int qtd;
    struct _product *next, *prev;
};typedef struct _product Products;

typedef struct{
    Products *head;
    Products *tail;
}LProducts;

struct _cart {
   int codeprod;
   int qt_buy;
   float price;
   char name[30];
   int id;
   struct _cart *next, *prev;
};typedef struct _cart Cart;

typedef struct{
    Cart *head;
    Cart *tail;
}LCart;

int check_code(LProducts *list, int code){
    Products *aux = malloc(sizeof(Products));
    aux = list->head;

    while (aux != NULL){
        if(aux->code == code){
            printf("Codigo ja cadastrado, tente novamente!\n");
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

void insert_product(LProducts *list){
    Products *new = malloc(sizeof(Products));
    Products *aux = list->head;
    int code;
    float price;
    int qtd;

    printf("Código: ");
    scanf("%d", &code);
    new->code = code;
    if (check_code(list, code) == 1){
        return;
    }
    printf("Nome: ");
    scanf("%s", new->name);
    printf("Valor por unidade(R$): ");
    scanf("%f", &price);
    new->price = price;
    printf("Quantidade: ");
    scanf("%d", &qtd);
    new->qtd = qtd;

    new->next = NULL;
    new->prev = NULL;

    if(list->head == NULL){
        list->head = new;
        list->tail = new;
        printf("Produto cadastrado com sucesso!\n");
        return;
    }

    while (aux->next != NULL){
        aux = aux->next;
    }

    if(aux == list->head){
        list->head->next = new;
        new->prev = list->head;
        list->tail = new;
    }else{
        aux->next = new;
        new->prev = aux;
        list->tail = new;
    }
    printf("Produto cadastrado com sucesso!\n");
    return;
}

void delete_product(LProducts *list){
    Products *aux = list->head;
    Products *anterior, *proximo;

    if(aux == NULL){
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    int code_aux;
    printf("Digite o código que deseja excluir: ");
    scanf("%d", &code_aux);
    
    while(aux != NULL){
        if (aux->code == code_aux){
            if(aux == list->head && aux == list->tail){
                list->head = NULL;
                list->tail = NULL;
            }
            else if (aux == list->head){
                list->head = list->head->next;
                list->head->prev = NULL;
            }
            else if(aux == list->tail){
                list->tail = list->tail->prev;
                list->tail->next = NULL;
            }
            else{
                anterior = aux->prev;
                proximo = aux->next;
                anterior->next = proximo;
                proximo->prev = anterior;
            }
            printf("Produto deletado com sucesso!");
            free(aux);
            break;
        }
        aux = aux->next;
    }
}

void printListByHead(LProducts *list){
    Products *aux = list->head;
    if(list->head == NULL){
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    printf("\nOs produtos cadastrados são: \n");
    while(aux != NULL){
        printf("(%d): %s %.2fR$; %d unidades\n",aux->code, aux->name, aux->price, aux->qtd);
        aux = aux->next;
    }
}

void searchProduct(LProducts *list){
    Products *aux = malloc(sizeof(Products));
    aux = list->head;
    int code, i=0;

    printf("Digite o código do protudo que deseja buscar: ");
    scanf("%d", &code);
    while(aux != NULL){
        if (aux->code == code){
            i++;
            break;
        }
        aux = aux->next;
    }
    if (i>0) 
        printf("\n(%d)%s %.2fR$; %d unidades\n",aux->code, aux->name, aux->price, aux->qtd);
    else 
        printf("Produto não cadastrado!\n");
}

int checkid(LCart *list_cart){
    Cart *aux = list_cart->head;
    int id=0;
    while(aux!=NULL){
        id++;
        aux=aux->next;
    }
    return id;
}

void insert_cartItem(LCart *list_cart, LProducts *list){
    Cart *new = malloc(sizeof(Cart));
    Cart *aux = list_cart->head;
    Products *aux2 = list->head;
    int code, qt, id=0;

    printf("Código: ");
    scanf("%d", &code);
    new->codeprod = code;
    printf("Quantidade: ");
    scanf("%d", &qt);
    while(aux2!=NULL){
        if(code == aux2->code){
            if(aux2->qtd >= qt){
                aux2->qtd -= qt;
                new->qt_buy = qt;
                strcpy(new->name, aux2->name);
            }
            else{
                printf("A quantidade excede o máximo de estoque, tente novamente!\n");
                return;
            }     
            new->price = aux2->price * qt;
            id = checkid(list_cart);
            new->id = id;
        }
        aux2=aux2->next;
    }
    
    new->next = NULL;
    new->prev = NULL;

    if(list_cart->head == NULL){
        list_cart->head = new;
        list_cart->tail = new;
        return;
    }

    while (aux->next != NULL){
        aux=aux->next;
    }

    if(aux == list_cart->head){
        list_cart->head->next = new;
        new->prev = list_cart->head;
        list_cart->tail = new;
    }else{
        aux->next = new;
        new->prev = aux;
        list_cart->tail = new;
    }
    printf("Compra cadastrada com sucesso!\n");
    return;
}

float sumCart(LCart *list_cart){
    Cart *aux = list_cart->head;
    float sum=0;

    while(aux!=NULL){
        sum += aux->price;
        aux = aux->next;
    }
    return sum;
}

void delete_cartItem(LCart *list_cart, LProducts *list){
    Cart *aux = list_cart->head;
    Cart *anterior, *proximo;
    Products *i;
    int id;

    if(aux == NULL){
        printf("Carrinho Vazia!\n");
        return;
    }

    printf("Digite o ID da compra que deseja excluir: ");
    scanf("%d", &id);
    while(aux != NULL){
        if (aux->id == id){
            if(aux == list_cart->head && aux == list_cart->tail){
                list_cart->head = NULL;
                list_cart->tail = NULL;
            }
            else if (aux == list_cart->head){
                list_cart->head = list_cart->head->next;
                list_cart->head->prev = NULL;
            }
            else if(aux == list_cart->tail){
                list_cart->tail = list_cart->tail->prev;
                list_cart->tail->next = NULL;
            }
            else{
                anterior = aux->prev;
                proximo = aux->next;
                anterior->next = proximo;
                proximo->prev = anterior;
            }
            for(i=list->head; i!=NULL ; i=i->next){
                if (aux->codeprod == i->code){
                    i->qtd += aux->qt_buy;
                }
            }
            printf("Compra deletada do carrinho com sucesso!");
            free(aux);
            break;
        }
        aux = aux->next;
    }
}

void printListCartByHead(LCart *list_cart){
    Cart *aux = list_cart->head;
    if(list_cart->head == NULL){
        printf("\nCarrinho vazio!\n");
        return;
    }
    printf("\nAs compras no carrinho são: \n");
    while(aux != NULL){
        printf("%d unidade(s) de %s = %.2fR$ ID: %d\n", aux->qt_buy, aux->name, aux->price, aux->id);
        aux = aux->next;
    }
}

void freeCartMemory(LCart *list_cart){
    Cart *aux;

    while (list_cart->head != NULL) {
    aux = list_cart->head;
    list_cart->head = list_cart->head->next;
    free(aux);
    }
    printf("\n");
}

void menu_Cart(LProducts *list){
    LCart list_cart;
    int option = 1;
    float totalprice = 0;

    list_cart.head = NULL;
    list_cart.tail = NULL;

    while(option!=0){
        printf("\nEscolha a operação que deseja no carrinho:\n");
        printf("Inserir um item no carrinho(1)\n");
        printf("Excluir um item no carrinho(2)\n");
        printf("Consultar o carrinho(3)\n");
        printf("Consultar os produtos disponiveis(4)\n");
        printf("Finalizar compra(0)\n");
        scanf("%d",&option);
        if (option == 1) {
            insert_cartItem(&list_cart, list);
            totalprice = sumCart(&list_cart);
            printf("Valor total da compra: %.2fR$\n",totalprice);
        }
        if (option == 2){
            delete_cartItem(&list_cart, list);
            totalprice = sumCart(&list_cart);
            printf("\nValor total da compra: %.2fR$\n",totalprice);
        }
        if (option == 3) 
            printListCartByHead(&list_cart);
        if (option == 4)
            printListByHead(list);
        if (option == 0){
            printListCartByHead(&list_cart);
            freeCartMemory(&list_cart);
            printf("\nValor total da compra: %.2fR$\n\n",totalprice);
        }
    }
}

void freeMemory(LProducts *list){
    Products *aux;

    while (list->head != NULL) {
    aux = list->head;
    list->head = list->head->next;
    free(aux);
    printf("*");
    }
    printf("\n\n");
}
    
void menu(){
    int option = 1;
    LProducts list;
    list.head = NULL;
    list.tail = NULL;


    while(option!=0){
        printf("\nEscolha a operação que deseja:\n");
        printf("Cadastrar um produto (1)\n");
        printf("Listar produtos      (2)\n");
        printf("Buscar produto       (3)\n");
        printf("Excluir um produto   (4)\n");
        printf("Comprar produtos     (5)\n");
        printf("Sair do sistema      (0)\n");
        printf("\n");
        scanf("%d", &option);
        printf("\n");
        if (option==1){
            insert_product(&list);
        }
        else if(option==2)
            printListByHead(&list);  
        else if(option==3)
            searchProduct(&list);
        else if(option==4)
            delete_product(&list);
        else if(option==5)
            menu_Cart(&list);
        else if(option==0)
            freeMemory(&list);
    }
}

int main(){
    printf("\nBEM VINDO AO DIGNISSO PROGRAMA DE COMPRAS DA AMAZON\n");
    menu();

    return 0;
}
