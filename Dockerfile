FROM gcc:latest
RUN apt-get update && apt-get install -y libsdl2-dev
WORKDIR /usr/src/app
COPY . .
RUN make
CMD ["./rotating_cube"]