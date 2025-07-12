import socket

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
        server_address = ("localhost", 53444)
        server_socket.bind(server_address)

        while True:
            try:
                # Read data
                for i in range(1000):
                    data, client_address = server_socket.recvfrom(1460)

                # Send response
                response = "back at you UDP".encode()
                server_socket.sendto(response, client_address)

            except socket.error as e:
                print(f"Socket error: {e}")
            except Exception as e:
                print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()