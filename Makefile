COMPOSE = docker compose -f ./docker-compose.yml

all: clean build up
	@echo "Fortress started!"

prep:
	@ssh-keygen -f "$(HOME)/.ssh/known_hosts" -R "[localhost]:2222" 2>/dev/null || true

build: prep
	@echo "Building images..."
	$(COMPOSE) build

up:
	@echo "Upping all the containers..."
	$(COMPOSE) up -d

down:
	@echo "Stopping and removing containers..."
	$(COMPOSE) down

clean:
	@echo "Cleaning Docker..."
	@$(MAKE) -C ./honeypot clean --no-print-directory > /dev/null
	@$(MAKE) -C ./logger clean --no-print-directory > /dev/null
	@$(MAKE) -C ./analysis-engine clean --no-print-directory > /dev/null
	$(COMPOSE) down -v

fclean:
	@echo "Full cleaning Fortress..."
	@$(MAKE) -C ./honeypot fclean --no-print-directory > /dev/null
	@$(MAKE) -C ./logger fclean --no-print-directory > /dev/null
	@$(MAKE) -C ./analysis-engine fclean --no-print-directory > /dev/null
	$(COMPOSE) down -v --rmi all --remove-orphans

logs:
	@echo "Check specific service logs (ex: make logs SERVICE=honeypot)"
	$(COMPOSE) logs -f $(SERVICE)

exec:
	@echo "Entering on the container (ex: make exec SERVICE=honeypot)"
	$(COMPOSE) exec $(SERVICE) sh

re: clean build up
	@echo "Restarting all the containers..."

.PHONY: all prep build up down clean fclean logs exec re