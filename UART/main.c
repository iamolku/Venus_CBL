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

    //Set the terminal to non-blocking
    char buf[256];
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    while (1)
    {   
        //Read terminal
        int numRead = read(0, buf, 256);
        if(numRead > 0)    
        {
            uint32_t length = numRead - 1;
            uint8_t* len_bytes = (uint8_t*)&length; //Cast uint32_t to array of uint8_t
            printf("<< Outgoing Message: Size = %d\n", length);
            fflush(NULL);
            for(uint32_t i = 0; i < 4; i++)
            {
                uart_send(UART0, len_bytes[i]); //Send payload length in bytes
            }
            for(uint32_t i = 0; i < length; i++)
            {
                uart_send(UART0, buf[i]); //Send the payload bytes
            }    
        }

    

        if(uart_has_data(UART0))
            {
            uint8_t read_len[4];
            for(uint32_t i = 0; i < 4; i++)
            {
                read_len[i] = uart_recv(UART0); //Read the payload length in bytes
            }
            uint32_t length = *((uint32_t*)read_len); //Cast array to uint32_t number. 
            printf(">> Incoming Message: Length = %d\n", length);
            fflush(NULL);
            uint32_t i = 0;    
            char* buffer = (char*) malloc(sizeof(char) * length);
            while(i < length)
            {
                buffer[i] = (char)uart_recv(UART0); // Read the payload into memory
                i++;
            }
            printf("  >%s\n", buffer);
            fflush(NULL);
            free(buffer);
        }
        /***************************************************/
    }
    fflush(NULL);
    uart_reset_fifos(UART0);
    uart_destroy(UART0);
    pynq_destroy();
    return 0;
}