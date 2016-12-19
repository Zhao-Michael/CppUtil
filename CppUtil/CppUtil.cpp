#include <Util.h>
#include <Any.h>


int main()
{
	int money, i, k; float fund, net_value[6], to_va_in[5], sum = 0;

	float Current_Value[6];


begin:

	printf(" Please input your money(>=1000, and multiple): ");

	scanf("%d", &money);

	if (money % 1000 != 0)
	{
		printf("\n %d is not multiple of 1000.\n\n", money);
		goto begin;
	}

	fund = money*.985;

	net_value[0] = 1;

	printf("\n Please input everyday net value in this week: \n\n");

	for (i = 1; i < 6; i++)
	{
		printf(" "); scanf("%f", &net_value[i]);
	}

	printf("Quotient    Net Value    Increase Rate    Current Value    Current Payoff\n\n");

	for (i = 1; i < 6; i++)
	{
		to_va_in[i - 1] = 100 * (net_value[i] - net_value[i - 1]) / net_value[i - 1];

		Current_Value[i - 1] = fund * net_value[i];
	}


	for (i = 0; i < 5; i++)
	{
		printf(" %.0f  %.4f  %.2f  %.0f   %.0f   \n\n", fund, net_value[i + 1], to_va_in[i], Current_Value[i], Current_Value[i] * 0.995 - money);

		sum += net_value[i + 1];
	}

	printf(" Average Net Value in this week = %.5f\n\n", sum / 5);

	getchar();

	getchar();
}
