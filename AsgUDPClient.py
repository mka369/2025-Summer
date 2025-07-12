import socket
import time

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client_socket:
        server_address = ("localhost", 53444)
        message = "hello UDP".encode()
        
        try:
            # Send data to the server
            start_time = time.perf_counter_ns()
            client_socket.sendto(message, server_address)
            data, _ = client_socket.recvfrom(1460)
            end_time = time.perf_counter_ns()

            # Calculate the round-trip time
            rtt = end_time - start_time
            print(f"Round-trip time: {rtt} ns")

        except socket.error as e:
            print(f"Socket error: {e}")
        except Exception as e:
            print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()