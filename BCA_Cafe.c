#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct items
{
	char item[20];
	float price;
	int qty;
};
struct orders
{
	char customer[50];
	char date[50];
	int numofItems;
	struct items itm[50];
};

// Function to generate bills
void generateBillHeader(char name[50], char date[30])
{
	printf("\n\n");

	printf("\t   BCA Cafe & Restaurant");
	printf("\n\t -------------------------");
	printf("\nDate: %s", date);
	printf("\nInvoice To : %s", name);
	printf("\n");
	printf("---------------------------------------\n");
	printf("Items\t\t");
	printf("Quanity\t\t");
	printf("Total\t\t\n");
	printf("---------------------------------------");
	printf("\n");
}

void generateBillBody(char item[30], int qty, float price)
{
	printf("%s\t", item);
	printf("%d\t\t", qty);
	printf("%.2f\t\t", price);
	printf("\n");
}

void generateBillFooter(float total)
{

	float dis = 0.1 * total;
	float netTotal = total - dis;
	float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
	printf("---------------------------------------\n");
	printf("Sub Total \t\t\t%.2f", total);
	printf("\nDiscount @10 %s\t\t\t%.2f", "%", dis);
	printf("\n\t\t\t\t--------");
	printf("\nNet Total\t\t\t%.2f", netTotal);
	printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
	printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
	printf("\n---------------------------------------\n");
	printf("Grand Total\t\t\t%.2f", grandTotal);
	printf("\n---------------------------------------\n");
}

int main()
{
	int opt, num;
	struct orders ord;
	struct orders order;
	char saveBill = 'y', contFlag = 'y';
	char name[50];
	FILE *fp;

	// dashboard
	while (contFlag == 'y')
	{
		float total = 0;
		int invoiceFound = 0;
		printf("\t\t                         BCA Cafe & Restaurant\n");
		printf("\n\nPlease select your operation");
		printf("\n\n1. Generate Invoice");
		printf("\n2. Show all Invoices");
		printf("\n3. Search Invoice");
		printf("\n4. Exit");
		printf("\n\n\tEnter your choice : ");
		scanf("%d", &opt);
		fgetc(stdin);

		switch (opt)
		{
		case 1:

			printf("\nEnter the name of customer : \t");
			fgets(ord.customer, 50, stdin);
			ord.customer[strlen(ord.customer) - 1] = 0;
			strcpy(ord.date, __DATE__);
			printf("Enter the number of items :\t");
			scanf("%d", &num);
			ord.numofItems = num;
			for (int i = 0; i < num; i++)
			{
				fgetc(stdin);
				printf("\n");
				printf("Enter the items %d : \t", i + 1);
				fgets(ord.itm[i].item, 20, stdin);
				ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
				printf("Enter the quantity :\t");
				scanf("%d", &ord.itm[i].qty);
				printf("Enter the unit price :\t");
				scanf("%f", &ord.itm[i].price);
				total += ord.itm[i].qty * ord.itm[i].price;
			}
			generateBillHeader(ord.customer, ord.date);
			for (int i = 0; i < ord.numofItems; i++)
			{
				generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
			}
			generateBillFooter(total);

			printf("\nDo you want to save the invoice [y/n] : ");
			scanf("%s", &saveBill);

			if (saveBill == 'y')
			{
				fp = fopen("RestaurantBill.dat", "a+");
				fwrite(&ord, sizeof(struct orders), 1, fp);
				if (fwrite != 0)
					printf("\n Successfully saved");
				else
					printf("\nError saving");
				fclose(fp);
			}
			break;

		case 2:

			fp = fopen("RestaurantBill.dat", "r");
			printf("\n\t\t\t\t\t  The Previous Inovices      \t\t\t\t\t   ");
			while (fread(&order, sizeof(struct orders), 1, fp))
			{
				float tot = 0;
				generateBillHeader(order.customer, order.date);
				for (int i = 0; i < order.numofItems; i++)
				{
					generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
					tot += order.itm[i].qty * order.itm[i].price;
				}
				generateBillFooter(tot);
			}
			fclose(fp);
			break;

		case 3:
			printf("Enter the name of customer : \t");
			fgets(name, 50, stdin);
			name[strlen(name) - 1] = 0;

			fp = fopen("RestaurantBill.dat", "r");
			printf("\n \t\t\t\t\t   Invoice of %s  \t\t\t\t\t  ", name);
			while (fread(&order, sizeof(struct orders), 1, fp))
			{
				float tot = 0;
				if (!strcmp(order.customer, name))
				{
					generateBillHeader(order.customer, order.date);
					for (int i = 0; i < order.numofItems; i++)
					{
						generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
						tot += order.itm[i].qty * order.itm[i].price;
					}
					generateBillFooter(tot);
					invoiceFound = 1;
				}
			}
			if (!invoiceFound)
			{
				printf("the invoice for %s does not exists", name);
			}

			fclose(fp);
			break;

		case 4:
			printf("\n\t\t the program is exit ");
			exit(0);
			break;

		default:
			printf("Sorry invalid option");
			break;
		}
		printf("\n\nDo you want to perfrom any another operation[y/n] : \t");
		scanf("%s", &contFlag);
	}
	printf("\n\n");
	return 0;
}