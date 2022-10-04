import asyncio
import websockets

async def hello():
    async with websockets.connect("ws://localhost:8765") as ws:
        await ws.send("Hello World!")
        await ws.recv()


asyncio.run(hello())