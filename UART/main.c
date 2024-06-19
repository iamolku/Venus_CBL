#include <libpynq.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    switchbox_init();
    switchbox_set_pin(IO_AR0, SWB_UART0_RX);
    switchbox_set_pin(IO_AR1, SWB_UART0_TX);
    uart_init(UART0);
    uart_reset_fifos(UART0);

    //For terminal input
    char buf[256];
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    while (1)
    {  
        if(uart_has_data(UART0))
            {
            uint8_t read_len[4];
            for(uint32_t i = 0; i < 4; i++)
            {
                read_len[i] = uart_recv(UART0);
            }
            uint32_t length = *((uint32_t*)read_len);
            printf(">> Incoming Message: Length = %d\n", length);
            fflush(NULL);
            uint32_t i = 0;
            char* buffer = (char*) malloc(sizeof(char) * length);
            while(i < length)
            {
                buffer[i] = (char)uart_recv(UART0);
                i++;
            }
            printf("  >%s\n", buffer);
            fflush(NULL);
            free(buffer);
        }
        
        
        //Read terminal
        int numRead = read(0, buf, 256);
        if(numRead > 0)    
        {
            uint32_t length = numRead - 1;
            uint8_t* len_bytes = (uint8_t*)&length;
            printf("<< Outgoing Message: Size = %d\n", length);
            fflush(NULL);
            for(uint32_t i = 0; i < 4; i++)
            {
                uart_send(UART0, len_bytes[i]);
            }
            for(uint32_t i = 0; i < length; i++)
            {
                uart_send(UART0, buf[i]);
            }    
        }
    }
    fflush(NULL);
    uart_reset_fifos(UART0);
    uart_destroy(UART0);
    pynq_destroy();
    return 0;
}
