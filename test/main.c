#include <stdio.h>
#include "ft_printf.h"

int		main(void)
{

	#pragma clang diagnostic ignored "-Wformat"
	
	// int len = 0;
	// ft_printf("Width test: %10.12s\n", "helloimalongstring");
	// len = printf("Width test: %10.12s\n", "helloimalongstring");
	// printf("\nprintf len = %i\n", len);

	// int len = 0;
	// ft_printf("Plus/minus test % +d!\n", 10);
	// len = printf("Plus/minus test % +d!\n", 10);
	// printf("printf len = %i\n", len);

	// int len = 0;
	// ft_printf("Width test: %10s, octal %#10X\n", "kiss", 100);
	// len = printf("Width test: %10s, octal %#10X\n", "kiss", 100);
	// printf("\nprintf len = %i\n", len);

	// int len = 0;
	// ft_printf("Hello %10.6s! I'm Juli%c, I'm %d y.o. In Russia is %i degrees now.", "peopleAAA", 'a', 26, -15);
	// len = printf("Hello %10.6s! I'm Juli%c, I'm %d y.o. In Russia is %i degrees now.", "peopleAAA", 'a', 26, -15);
	// printf("\nprintf len = %i\n", len);

	// int	a = 23;
	// int len = 0;
	// ft_printf("Pointer address test %25p \' \"", &a);
	// len = printf("Pointer address test %25p \' \"", &a);
	// printf("\nprintf len = %i\n", len);

	// int len = 0;
	// char *format = "now let's check %s! %x its a %i in hex, 100 its %o in octal\n";
	// ft_printf(format, "digits", 10, 10, 100);	
	// len = printf("now let's check %s! %x its a %i in hex, 100 its %o in octal\n", "digits", 10, 10, 100);
	// printf("\nprintf len = %i\n", len);

	// int len = 0;
	// ft_printf("here's pound flag %#o, %#x\n", 42, 12);
	// len = printf("here's pound flag %#o, %#x\n", 42, 12);
	// printf("\nprintf len = %i\n", len);

	// int my_ptr = 0;
	// int ptr = 0;
	// int len = 0;
	// ft_printf("\\ %% Unsigned decimal: %u. Stop and look how many chars were%n printed before 'printed' word: ", 36000, &my_ptr);
	// printf("%i\n", my_ptr);
	// len = printf("\\ %% Unsigned decimal: %u. Stop and look how many chars were%n printed before 'printed' word: ", 36000, &ptr);
	// printf("chars before 'printed' : %i\n", ptr);
	// printf("\nprintf len = %i\n", len);

	// int len = 0;
	// ft_printf("Test precision %.10d, '%.1s' instead of 'hello', %.i\n", 12345, "hello", 54321);
	// len = printf("Test precision %.10d, '%.1s' instead of 'hello', %.i\n", 12345, "hello", 54321);
	// printf("printf len = %i\n", len);

	// int len = 0;
	// ft_printf("%16.10i\n", 12345);
	// len = printf("%16.10i\n", 12345);
	// printf("\nprintf len = %i\n", len);


	// int len = 0;
	// ft_printf("Test len_mod: %ld, %hhi, %O, %hd, %llx\n", 12345, 123456, 12345, 123456, 12345);
	// len = printf("Test len_mod: %ld, %hhi, %O, %hd, %llx\n", 12345, 123456, 12345, 123456, 12345);
	// printf("printf len = %i\n", len);

	// // Bad cases:
	//int len1 = 0;
	//int len2 = 0;
	//int len3 = 0;
	//ft_printf("%#x", 0);
	//ft_printf("@moulitest: %.x %.0x", 0, 0);
	//ft_printf("@moulitest: %5.x %5.0x<--", 0, 0);
	//len1 = printf("%#x", 0);
	//printf("\nprintf len = %i\n", len1);
	//len2 = printf("@moulitest: %.x %.0x", 0, 0);
	//printf("\nprintf len = %i\n", len2);
	//len3 = printf("@moulitest: %5.x %5.0x<--", 0, 0);
	//printf("\nprintf len = %i\n", len3);

	int len = 0;
	int my_len = 0;
	my_len = ft_printf("% Zoooo");
	printf("\nmy return len = %i\n", my_len);
	len = printf("% Zoooo");
	printf("\nprintf len = %i\n", len);
	return(0);
}
