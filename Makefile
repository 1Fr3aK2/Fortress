COMPOSE = docker compose -f ./docker-compose.yml
VOLUMES = ./logs ./keys
SERVICES = honeypot logger

all: clean build up
	@echo "Fortress started!"

prep:
	@echo "Building volumes directories..."
	mkdir -p $(VOLUMES)

build: prep
	@echo "Building images..."
	$(COMPOSE) build

up:
	@echo "Upping all the containers..."
	$(COMPOSE) up -d

down:
	@echo "Stopping and removing containers..."
	$(COMPOSE) down -v

clean:
	@echo "Cleaning Docker..."
	$(COMPOSE) down -v
	docker system prune -f
	rm -rf ./logs

fclean:
	@echo "Full cleaning Docker..."
	-docker stop $$(docker ps -qa)
	-docker rm $$(docker ps -qa)
	-docker rmi -f $$(docker images -qa)
	-docker volume rm $$(docker volume ls -q)
	-docker network rm $$(docker network ls -q) 2>/dev/null
	rm -rf ./logs

logs:
	@echo "Check specific service logs (ex: make logs SERVICE=honeypot)"
	$(COMPOSE) logs -f $(SERVICE)

exec:
	@echo "Entering on the container (ex: make exec SERVICE=honeypot)"
	$(COMPOSE) exec $(SERVICE) sh

re: clean build up
	@echo "Restarting all the containers..."

.PHONY: all build up down clean fclean logs exec re prep
