import asyncio
import pathlib
import ssl
from threading import local
import websockets


ssl_context = ssl.SSLContext(ssl.PROTOCOL_TLS_CLIENT)
localhost_pem = pathlib.Path(__file__).with_name("localhost.pem")
ssl_context.load_verify_locations(localhost_pem)


async def hello():
    url ="wss://localhost:100"
    async with websockets.connect(url, ssl= ssl_context) as websocket:
        name = input("What is your name: ")

        await websocket.send(name)

        print(f" >>> {name}")

        greeting = await websocket.recv()
        print(f"<<< {greeting}")
if __name__ == "__main__":

    asyncio.run(hello())