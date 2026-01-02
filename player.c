#include "player.h"

player_t player_from_csv_str(const char *csv_str) {
    player_t player;

    int idx = 0;
    char *name = malloc(sizeof(char) * MAX_NAME_LENGTH + 1);
    while (csv_str[idx] != ',') {
        name[idx] = csv_str[idx];
        idx++;
    }

    name[idx] = '\0';
    idx++;

    char number[10];
    char number_idx = 0;
    while (csv_str[idx] != '\0') {
        number[number_idx] = csv_str[idx];
        idx++;
        number_idx++;
    }
    number[number_idx] = '\0';

    player.name = name;
    player.score = atoi(number);

    return player;
}

players_t *create_players() {
    players_t *players = malloc(sizeof(players_t));

    if (players == NULL) {
        exit(EXIT_FAILURE);
    }

    players->length = 0;
    players->capacity = 10;
    players->items = malloc(sizeof(player_t) * players->capacity);

    if (players->items == NULL) {
        exit(EXIT_FAILURE);
    }

    return players;
}

void destroy_players(players_t *players) {
    for (int i = 0; i < players->length; i++) {
        free(players->items[i].name);
    }
    free(players->items);
    free(players);
}

players_t *load_players_data() {
    players_t *players = create_players();

    FILE *file = fopen(STATS_FILE_NAME, "r");

    if (file == NULL) {
        fopen(STATS_FILE_NAME, "w");
        file = fopen(STATS_FILE_NAME, "r");
    }

    char line[20];

    while (fgets(line, 20, file)) {
        line[strcspn(line, "\n")] = 0;
        array_append(players, player_from_csv_str(line));
    }

    fclose(file);

    return players;
}

void save_players_data(const players_t *players) {
    FILE *file = fopen(STATS_FILE_NAME, "w");

    for (int i = 0; i < players->length; i++) {
        fprintf(file, "%s,%d\n", players->items[i].name, players->items[i].score);
    }

    fclose(file);
}

int find_player_by_name(const player_t player, const players_t *players) {
    int idx = -1;

    for (int i = 0; i < players->length; i++) {
        if (strcmp(players->items[i].name, player.name) == 0) {
            idx = i;
            break;
        }
    }

    return idx;
}

int compare_scores(const void *a, const void *b) {
    const player_t *p1 = a;
    const player_t *p2 = b;

    return (p1->score - p2->score);
}

void sort_players_by_score(const players_t *players) {
    if (!players || players->length < 2) return;

    qsort(players->items, players->length, sizeof(player_t), compare_scores);
}

char *concatenate(const char *a, const char *b, const char *c) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);
    size_t clen = strlen(c);
    char *res = malloc(alen + blen + clen + 1);

    if (res == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy(res, a, alen);
    memcpy(res + alen, b, blen);
    memcpy(res + alen + blen, c, clen + 1);

    return res;
}

char *get_player_name() {
    const char info[] = "Enter your name: ";
    const point_t center = calc_middle_position(strlen(info),1);
    mvprintw(center.y - 1, center.x, info);

    char underline[MAX_NAME_LENGTH + 1];
    memset(underline, '_', MAX_NAME_LENGTH);
    underline[MAX_NAME_LENGTH] = '\0';

    mvprintw(center.y + 1, center.x, "%s", underline);
    move(center.y + 1, center.x);
    char *name = get_str(MAX_NAME_LENGTH);

    if (strlen(name) == 0) {
        strcpy(name, "unknown");
    }

    clear();
    refresh();

    return name;
}

int save_player_best_score(player_t player) {
    players_t *players = load_players_data();

    const int player_idx = find_player_by_name(player, players);
    bool data_updated = false;
    int best_score = player.score;

    if (player_idx == -1) {
        char *name_cpy = strdup(player.name);
        const player_t p = {name_cpy, player.score};
        array_append(players, p);
        data_updated = true;
    } else if (player.score > players->items[player_idx].score){
        players->items[player_idx].score = player.score;
        data_updated = true;
    } else {
        best_score = players->items[player_idx].score;
    }

    if (data_updated) {
        save_players_data(players);
    }

    destroy_players(players);

    return best_score;
}

strings_t *get_sorted_players() {
    players_t *players = load_players_data();
    sort_players_by_score(players);

    strings_t *strings = init_strings();

    for (int i = 0; i < players->length; i++) {
        char score[10];
        sprintf(score, "%d", players->items[i].score);
        char *full_player_info = concatenate(players->items[i].name, " ", score);
        array_append(strings, full_player_info);
    }

    destroy_players(players);

    return strings;
}