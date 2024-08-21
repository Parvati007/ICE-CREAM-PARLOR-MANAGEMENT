#include <stdio.h>
#include <stdlib.h>

struct ice_cream {
    int id;
    char name[50];
    int price;
    int stock;
};

void display_menu();
void add_ice_cream();
void update_ice_cream();
void search_ice_cream();
void delete_ice_cream();

int main() {
    int choice;
     do {
         display_menu();
         scanf("%d", &choice);
         switch(choice) {
             case 1:
             	display_ice_creamlist();
                
                break;
             case 2:
             	add_ice_cream();
                
                break;
             case 3:
             	update_ice_cream();
                
                break;
             case 4:
             	search_ice_cream();
                
                break;
             case 5:
             	delete_ice_cream();
             	
             	break;
             case 6:
             	printf("Exiting program...\n");
                exit(0);
                break;
			      
             default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

void display_menu() {
    printf("Ice Cream Management System\n");
    printf("\n");
    printf("l. List of ice cream\n");
    printf("2. Add ice cream\n");
    printf("3. Update ice cream\n");
    printf("4. Search ice cream\n");
    printf("5. Delete ice cream\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void display_ice_creamlist(){
       
     FILE *fp;
    struct ice_cream ic;
    fp=fopen("ice_creams.dat","r");
    
     printf("\t\t\t\t======= ICE CREAM RECORD =======\n\n\n");
      
    if(fp==NULL){
        
        fprintf(stderr,"can't open file\n");
        exit(0);
    }else{
        printf("\t\t\t\tRECORDS :\n");
        printf("\t\t\t\t___________\n\n");
    }
        
        while(fread(&ic, sizeof(ic), 1, fp)){
         printf("\n\t\t\t\t ID  : %d",ic.id);
         printf("\n\t\t\t\t Name  : %s",ic.name);
         printf("\n\t\t\t\t Price  : %d",ic.price);
         printf("\n\t\t\t\t Stock : %d",ic.stock);
   
         printf("\n\t\t\t\t ________________________________\n");
      
         }
        fclose(fp);
        getch();
      
  }


void add_ice_cream() {
    struct ice_cream ic;
    FILE *fp;
    fp = fopen("ice_creams.dat", "ab");

    printf("\nEnter ice cream details:\n");
    printf("ID: ");
    scanf("%d", &ic.id);
    printf("Name: ");
    scanf("%s", &ic.name);
    printf("Price: ");
    scanf("%d", &ic.price);
    printf("Stock: ");
    scanf("%d", &ic.stock);

    fwrite(&ic, sizeof(ic), 1, fp);
    fclose(fp);

    printf("Ice cream added successfully.\n");
}

void update_ice_cream() {
    int id;
    struct ice_cream ic;
    FILE *fp;
    fp = fopen("ice_creams.dat", "rb+");

    printf("\nEnter ID of ice cream to update: ");
    scanf("%d", &id);

    while(fread(&ic, sizeof(ic), 1, fp)) {
        if(ic.id == id) {
            printf("\nEnter new details for ice cream:\n");
            printf("ID: ");
            scanf("%d", &ic.id);
            printf("Name: ");
            scanf("%s", &ic.name);
            printf("Price: ");
            scanf("%d", &ic.price);
            printf("Stock: ");
            scanf("%d", &ic.stock);

            fseek(fp, -(long)sizeof(ic), SEEK_CUR);
            fwrite(&ic, sizeof(ic), 1, fp);
            fclose(fp);

            printf("Ice cream updated successfully.\n");
            return;
        }
    }

    fclose(fp);
    printf("Ice cream not found.\n");
}

void search_ice_cream() {
    int id;
    struct ice_cream ic;
    FILE *fp;
    fp = fopen("ice_creams.dat", "r");

    printf("\nEnter ID of ice cream to search: ");
    scanf("%d", &id);

    while(fread(&ic, sizeof(ic), 1, fp)) {
        if(ic.id == id) {
            printf("\nID: %d\n", ic.id);
            printf("Name: %s\n", ic.name);
            printf("Price: %d\n", ic.price);
        }
    }
    fclose(fp);
}

void delete_ice_cream() {
     int id,count=0;
     struct ice_cream ic;
     FILE *fp, *temp_fp;
     fp = fopen("ice_creams.dat", "r");
     temp_fp = fopen("temp.dat", "w");

     if (fp == NULL) {
        printf("Error opening file.\n");
        return;
     }

     printf("Enter ID of ice cream to delete: ");
     scanf("%d", &id);

     while (fread(&ic, sizeof(ic), 1, fp)) {
        if (ic.id == id) {
            count=1; // skip the record we want to delete
        }
        else{
        	 fwrite(&ic, sizeof(ic), 1, temp_fp);
		 }
      }

     fclose(fp);
     fclose(temp_fp);
     if(!count){
    	printf("\nrecord not found");
	 }
	 if(count){

     remove("ice_creams.dat");
     rename("temp.dat", "ice_creams.dat");
     printf("Ice cream record deleted successfully.\n");
   	}
}