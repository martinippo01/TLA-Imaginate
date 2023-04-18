# Use the Ubuntu base image
FROM ubuntu:latest

# Update package list and install necessary dependencies
RUN apt-get update && \
    apt-get install -y \
    bison \
    cmake \
    flex \
    gcc \
    make

# Set the working directory inside the container
WORKDIR /project

