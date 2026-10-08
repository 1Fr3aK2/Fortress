COMPOSE = docker compose -f ./docker-compose.yml
SERVICES = honeypot logger analyser

# UIDs usados nos Dockerfiles (USER de cada serviço)
UID_ANALYSER = 10001
UID_LOGGER   = 10002
UID_HONEYPOT = 10003

all: clean build up
	@echo "Fortress started!"

prep:
	@ssh-keygen -f "$(HOME)/.ssh/known_hosts" -R "[localhost]:2222" 2>/dev/null || true

setup-logs:
	@echo "Preparing log directories..."
	mkdir -p logs/events logs/logs logs/alerts
	chmod 755 logs
	sudo chown -R $(UID_HONEYPOT):$(UID_HONEYPOT) logs/events
	sudo chown -R $(UID_LOGGER):$(UID_LOGGER) logs/logs
	sudo chown -R $(UID_ANALYSER):$(UID_ANALYSER) logs/alerts

build: prep
	@echo "Building images..."
	$(COMPOSE) build

up: setup-logs
	@echo "Upping all the containers..."
	$(COMPOSE) up -d

down:
	@echo "Stopping and removing containers..."
	$(COMPOSE) down -v

clean:
	@echo "Cleaning Docker..."
	@$(MAKE) -C ./honeypot clean --no-print-directory > /dev/null
	@$(MAKE) -C ./logger clean --no-print-directory > /dev/null
	@$(MAKE) -C ./analysis-engine clean --no-print-directory > /dev/null
	$(COMPOSE) down -v
	docker system prune -f
	sudo rm -rf ./logs

fclean:
	@echo "Full cleaning Docker..."
	@$(MAKE) -C ./honeypot fclean --no-print-directory > /dev/null
	@$(MAKE) -C ./logger fclean --no-print-directory > /dev/null
	@$(MAKE) -C ./analysis-engine fclean --no-print-directory > /dev/null
	-docker stop $$(docker ps -qa)
	-docker rm $$(docker ps -qa)
	-docker rmi -f $$(docker images -qa)
	-docker volume rm $$(docker volume ls -q)
	-docker network rm $$(docker network ls -q) 2>/dev/null
	sudo rm -rf ./logs

logs:
	@echo "Check specific service logs (ex: make logs SERVICE=honeypot)"
	$(COMPOSE) logs -f $(SERVICE)

exec:
	@echo "Entering on the container (ex: make exec SERVICE=honeypot)"
	$(COMPOSE) exec $(SERVICE) sh

re: clean build up
	@echo "Restarting all the containers..."

.PHONY: all prep setup-logs build up down clean fclean logs exec re