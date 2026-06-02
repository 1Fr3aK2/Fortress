#!/bin/bash

echo "╔══════════════════════════════════════╗"
echo "║        FORTRESS — Daily Report       ║"
printf "║         %s         ║\n" "$(date -u '+%Y-%m-%d %H:%M UTC')"
echo "╚══════════════════════════════════════╝"

FILE="../logs/stats.json"

TATTEMPTS=$(grep '"total_attempts"' "$FILE" | sed 's/.*: \([0-9]*\).*/\1/')
L1H=$(grep '"attempts_last_1h"' "$FILE" | sed 's/.*: \([0-9]*\).*/\1/')
L24H=$(grep '"attempts_last_24h"' "$FILE" | sed 's/.*: \([0-9]*\).*/\1/')

printf "Total attempts: %s\n" "$TATTEMPTS"
printf "Last 1h:        %s\n" "$L1H"
printf "Last 24h:       %s\n\n" "$L24H"

echo -e "TOP PASSWORDS:\n"

i=1

grep '"password"' "$FILE" | \
sed 's/.*"password": "\([^"]*\)".*/\1/' | \
while IFS= read -r password
do
    count=$(grep -A1 "\"password\": \"$password\"" "$FILE" | \
            grep '"count"' | \
            sed 's/.*: \([0-9]*\).*/\1/')

    printf "%d. %s\t(%s attempts)\n" "$i" "$password" "$count"

    i=$((i + 1))

    [ "$i" -gt 10 ] && break
done

echo -e "\nTOP IPs:\n"

i=1

grep '"ip"' "$FILE" | \
sed 's/.*"ip": "\([^"]*\)".*/\1/' | \
while IFS= read -r ip
do
    count=$(grep -A1 "\"ip\": \"$ip\"" "$FILE" | \
            grep '"count"' | \
            sed 's/.*: \([0-9]*\).*/\1/')

    printf "%d. %s\t(%s attempts)\n" "$i" "$ip" "$count"

    i=$((i + 1))

    [ "$i" -gt 10 ] && break
done