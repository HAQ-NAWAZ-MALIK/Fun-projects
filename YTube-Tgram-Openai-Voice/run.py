from fastapi import FastAPI  # Importing the FastAPI framework

from app import router  # Importing the router module from the app package

app = FastAPI()  # Creating an instance of the FastAPI application

app.include_router(router)  # Including the router in the application
