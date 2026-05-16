// RAILWAY MANAGEMENT SYSTEM
// ~ Developed By RAHUL GUPTA
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
// -----------------------------------------------------------------------------------------------------------------------------
const int PROGRESS_SCREEN = 100;
// -----------------------------------------------------------------------------------------------------------------------------
// ALL STRUCTURES ARE HERE
typedef struct time
{
    int hour;
    int minute;
    char am_pm[3];
} t;
typedef struct route
{
    char station_name[50];
    t arrival;
    t departure;
} r;
typedef struct train_info
{
    int train_no;
    char train_name[50];
    t arrival;
    t depart;
    char start_station[50];
    char end_station[50];
    char run_days[100];
    int via_count;
    r via[100];
} train;
typedef struct user_id
{
    int id;
    int password;
} uid;
typedef struct task_struct
{
    int id;
    int initial_progress;
    int steps;
} task;
// -----------------------------------------------------------------------------------------------------------------------------
// ALL FUNCTIONS ARE HERE
void program_starter();
void clr_scr();
void clear_input();
void print_task_ui(task task_info);
void progress_bar_print();
void user_interface();
void admin_checker();
void add_train_info();
void train_info_changer();
char *day_checker(int, int, int);
int case_insensitive_compare(const char *, const char *);
int valid_date(int, int, int);
int valid_time(int, int, const char *);
void train_info_checker();
void train_info_start_end();
void program_exit();
// ------------------------------------------------------------------------------------------------------------------------------
int main()
{
    srand(time(NULL));
    printf("\nWelcome to the Railway Enquiry Window");
    printf("\n\nAre you an admin or a user?");
    program_starter();
    return 0;
}
// ------------------------------------------------------------------------------------------------------------------------------
void clear_input()
{
    while (getchar() != '\n')
        ;
}
// ------------------------------------------------------------------------------------------------------------------------------
void clr_scr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
// ------------------------------------------------------------------------------------------------------------------------------
void print_task_ui(task task_info)
{
    int bar_length = (PROGRESS_SCREEN * task_info.initial_progress) / 100;
    printf("\n[");
    for (int k = 0; k < PROGRESS_SCREEN; k++)
    {
        if (k < bar_length)
            printf("~");
        else
            printf(" ");
    }
    printf("] %d%%", task_info.initial_progress);
}
// ------------------------------------------------------------------------------------------------------------------------------
void progress_bar_print()
{
    task task_info[1];
    for (int j = 0; j < 1; j++)
    {
        task_info[j].id = j + 1;
        task_info[j].initial_progress = 0;
        task_info[j].steps = rand() % 21 + 10;
    }

    int tasks_incomplete = 1;
    while (tasks_incomplete)
    {
        tasks_incomplete = 0;
        clr_scr();
        for (int i = 0; i < 1; i++)
        {
            task_info[i].initial_progress += task_info[i].steps;
            if (task_info[i].initial_progress < 100)
            {
                tasks_incomplete = 1;
            }
            else if (task_info[i].initial_progress > 100)
            {
                task_info[i].initial_progress = 100;
            }

            print_task_ui(task_info[i]);
            printf("\nPlease Wait..\n");
        }
        sleep(1);
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
int case_insensitive_compare(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0');
}
// ------------------------------------------------------------------------------------------------------------------------------
int valid_time(int h, int m, const char *ampm)
{
    if (h < 1 || h > 12)
        return 0;
    if (m < 0 || m > 59)
        return 0;
    if (strcasecmp(ampm, "am") != 0 && strcasecmp(ampm, "pm") != 0)
        return 0;
    return 1;
}
// ------------------------------------------------------------------------------------------------------------------------------
void program_starter()
{
    int n;
    printf("\n1. Admin");
    printf("\n2. User");
    printf("\nEnter your choice : ");
    scanf("%d", &n);
    clear_input();

    switch (n)
    {
    case 1:
        clr_scr();
        sleep(1);
        admin_checker();
        break;
    case 2:
        clr_scr();
        sleep(1);
        user_interface();
        break;
    default:
        clr_scr();
        printf("\nInvalid choice!");
        printf("\nAn Error Occurred!!! Please restart the program.");
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
void program_exit()
{
    printf("\nExiting Window!!!");
    sleep(1);
    printf("\nSuccessfully Exited..");
    printf("\nThanks for visiting.....\n");
    sleep(1);
    printf("\n\n~ Developed by RAHUL GUPTA");
    sleep(1);
    return;
}
// ------------------------------------------------------------------------------------------------------------------------------
void admin_checker()
{
    FILE *fp = fopen("admin_record.txt", "r");
    if (fp == NULL)
    {
        printf("\nSorry! Server not working.\nPlease try again later..\n");
        return;
    }

    int id_taken, password_taken;
    printf("\nUser id: ");
    scanf("%d", &id_taken);
    printf("Password: ");
    scanf("%d", &password_taken);
    clear_input();

    uid temp;
    int found = 0;

    while (fscanf(fp, "%d %d", &temp.id, &temp.password) == 2)
    {
        if (temp.id == id_taken && temp.password == password_taken)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
    {
        int choice;
        progress_bar_print();
        printf("\nLogin successful! Welcome Admin.\n");
        sleep(1);
        clr_scr();
        printf("\n1. Add more train information.");
        printf("\n2. Change train information.");
        printf("\n3. Exit");
        printf("\nEnter your choice here : ");
        scanf("%d", &choice);
        clear_input();

        if (choice == 1)
        {
            clr_scr();
            add_train_info();
        }
        else if (choice == 2)
        {
            clr_scr();
            train_info_changer();
        }
        else
        {
            clr_scr();
            program_exit();
        }
    }
    else
    {
        clr_scr();
        progress_bar_print();
        printf("\nInvalid credentials. Access denied.\n");
        sleep(1);
        clr_scr();
        program_starter();
        clr_scr();
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
char *day_checker(int d, int m, int y)
{
    static char *days[] = {
        "Saturday", "Sunday", "Monday",
        "Tuesday", "Wednesday", "Thursday", "Friday"};

    if (m < 3)
    {
        m += 12;
        y -= 1;
    }

    int K = y % 100;
    int J = y / 100;

    int h = (d + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    return days[h];
}
// ------------------------------------------------------------------------------------------------------------------------------
int valid_date(int d, int m, int y)
{
    if (y < 1900 || m < 1 || m > 12 || d < 1)
        return 0;

    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
        days_in_month[1] = 29;

    return d <= days_in_month[m - 1];
}
// ------------------------------------------------------------------------------------------------------------------------------
void add_train_info()
{
    train t_info;
    FILE *fp = fopen("train_record.txt", "a");
    if (fp == NULL)
    {
        printf("\nError opening train record file!\n");
        return;
    }

    printf("\nEnter train no.: ");
    scanf("%d", &t_info.train_no);
    clear_input();

    printf("Enter train name: ");
    fgets(t_info.train_name, 50, stdin);
    t_info.train_name[strcspn(t_info.train_name, "\n")] = '\0';

    do
    {
        printf("Enter journey start time (hour minute am/pm): ");
        scanf("%d %d %2s", &t_info.arrival.hour, &t_info.arrival.minute, t_info.arrival.am_pm);
        clear_input();
    } while (!valid_time(t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm));

    do
    {
        printf("Enter journey end time (hour minute am/pm): ");
        scanf("%d %d %2s", &t_info.depart.hour, &t_info.depart.minute, t_info.depart.am_pm);
        clear_input();
    } while (!valid_time(t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm));

    printf("Enter start station: ");
    fgets(t_info.start_station, 50, stdin);
    t_info.start_station[strcspn(t_info.start_station, "\n")] = '\0';

    printf("Enter end station: ");
    fgets(t_info.end_station, 50, stdin);
    t_info.end_station[strcspn(t_info.end_station, "\n")] = '\0';

    int n;
    printf("Enter the number of running days in the week: ");
    scanf("%d", &n);
    clear_input();

    t_info.run_days[0] = '\0';
    for (int i = 0; i < n; i++)
    {
        char day[15];
        printf("Enter running day %d: ", i + 1);
        fgets(day, sizeof(day), stdin);
        day[strcspn(day, "\n")] = '\0';

        if (strlen(t_info.run_days) + strlen(day) + 2 < sizeof(t_info.run_days))
        {
            strcat(t_info.run_days, day);
            if (i < n - 1)
                strcat(t_info.run_days, ",");
        }
    }

    printf("Enter number of intermediate stations: ");
    scanf("%d", &t_info.via_count);
    clear_input();

    for (int i = 0; i < t_info.via_count; i++)
    {
        printf("\nStation %d name: ", i + 1);
        fgets(t_info.via[i].station_name, 50, stdin);
        t_info.via[i].station_name[strcspn(t_info.via[i].station_name, "\n")] = '\0';

        do
        {
            printf("Arrival time (hh mm am/pm): ");
            scanf("%d %d %2s",
                  &t_info.via[i].arrival.hour,
                  &t_info.via[i].arrival.minute,
                  t_info.via[i].arrival.am_pm);
            clear_input();
        } while (!valid_time(t_info.via[i].arrival.hour, t_info.via[i].arrival.minute, t_info.via[i].arrival.am_pm));

        do
        {
            printf("Departure time (hh mm am/pm): ");
            scanf("%d %d %2s",
                  &t_info.via[i].departure.hour,
                  &t_info.via[i].departure.minute,
                  t_info.via[i].departure.am_pm);
            clear_input();
        } while (!valid_time(t_info.via[i].departure.hour, t_info.via[i].departure.minute, t_info.via[i].departure.am_pm));
    }

    fprintf(fp, "%d|%s|%02d:%02d %s|%02d:%02d %s|%s|%s|%s|%d\n",
            t_info.train_no,
            t_info.train_name,
            t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm,
            t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm,
            t_info.start_station,
            t_info.end_station,
            t_info.run_days,
            t_info.via_count);

    for (int i = 0; i < t_info.via_count; i++)
    {
        fprintf(fp, "%s,%02d:%02d %s,%02d:%02d %s;",
                t_info.via[i].station_name,
                t_info.via[i].arrival.hour,
                t_info.via[i].arrival.minute,
                t_info.via[i].arrival.am_pm,
                t_info.via[i].departure.hour,
                t_info.via[i].departure.minute,
                t_info.via[i].departure.am_pm);
    }
    fprintf(fp, "\n");
    fclose(fp);
    progress_bar_print();
    printf("\n\nTrain information added successfully!\n");
    clr_scr();
    int b = 0;
    printf("\n1.Add more trains");
    printf("\n2.Change train information");
    printf("\n3.Exit");
    printf("\nEnter your choice: ");
    scanf("%d", &b);
    switch (b)
    {
    case 1:
        clr_scr();
        add_train_info();
        break;
    case 2:
        clr_scr();
        train_info_changer();
        break;
    case 3:
        clr_scr();
        program_exit();
        break;
    default:
        printf("\nInvalid choice!");
        sleep(1);
        clr_scr();
        admin_checker();
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
void user_interface()
{
    int choice;
    do
    {
        printf("\n1. Check train information.");
        printf("\n2. Check trains from source and destination.");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clear_input();

        switch (choice)
        {
        case 1:
            clr_scr();
            sleep(1);
            train_info_checker();
            break;
        case 2:
            clr_scr();
            sleep(1);
            train_info_start_end();
            break;
        case 3:
            clr_scr();
            sleep(1);
            program_exit();
            break;
        default:
            printf("\nInvalid choice!");
            sleep(1);
            clr_scr();
            user_interface();
        }
    } while (choice != 3);
}
// ------------------------------------------------------------------------------------------------------------------------------
void train_info_checker()
{
    int t_no;
    printf("\nEnter train number: ");
    scanf("%d", &t_no);
    clear_input();
    clr_scr();
    progress_bar_print();
    clr_scr();
    FILE *fp = fopen("train_record.txt", "r");
    if (fp == NULL)
    {
        printf("\nSorry! Server not working properly.\n");
        return;
    }

    train t_info;
    int found = 0;
    char route_line[1000];

    while (fscanf(fp, "%d|%49[^|]|%d:%d %2s|%d:%d %2s|%49[^|]|%49[^|]|%99[^|]|%d\n",
                  &t_info.train_no,
                  t_info.train_name,
                  &t_info.arrival.hour, &t_info.arrival.minute, t_info.arrival.am_pm,
                  &t_info.depart.hour, &t_info.depart.minute, t_info.depart.am_pm,
                  t_info.start_station,
                  t_info.end_station,
                  t_info.run_days,
                  &t_info.via_count) == 12)
    {
        fgets(route_line, sizeof(route_line), fp);

        if (t_info.train_no == t_no)
        {
            printf("\nTrain No: %d", t_info.train_no);
            printf("\nTrain Name: %s", t_info.train_name);
            printf("\nJourney Start Time: %02d:%02d %s",
                   t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm);
            printf("\nJourney End Time: %02d:%02d %s",
                   t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm);
            printf("\nRoute: %s -> %s", t_info.start_station, t_info.end_station);
            printf("\nRunning Days: %s", t_info.run_days);

            char *token = strtok(route_line, ";");
            int i = 0;
            while (token != NULL && i < t_info.via_count)
            {
                sscanf(token, "%49[^,],%d:%d %2s,%d:%d %2s",
                       t_info.via[i].station_name,
                       &t_info.via[i].arrival.hour,
                       &t_info.via[i].arrival.minute,
                       t_info.via[i].arrival.am_pm,
                       &t_info.via[i].departure.hour,
                       &t_info.via[i].departure.minute,
                       t_info.via[i].departure.am_pm);
                i++;
                token = strtok(NULL, ";");
            }

            printf("\n\nRoute: %s (Start)\n", t_info.start_station);
            for (int j = 0; j < t_info.via_count; j++)
            {
                printf(" -> %s [%02d:%02d %s - %02d:%02d %s]\n",
                       t_info.via[j].station_name,
                       t_info.via[j].arrival.hour,
                       t_info.via[j].arrival.minute,
                       t_info.via[j].arrival.am_pm,
                       t_info.via[j].departure.hour,
                       t_info.via[j].departure.minute,
                       t_info.via[j].departure.am_pm);
            }
            printf(" -> %s (End)\n", t_info.end_station);
            printf("==========================================================\n");
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
    {
        printf("\nTrain with number %d not found.\n", t_no);
        sleep(1);
        clr_scr();
        int b = 0;
        printf("\n1.Search another");
        printf("\n2.Check trains from source and destination.");
        printf("\n3.Exit");
        printf("\nEnter your choice here: ");
        scanf("%d", &b);
        switch (b)
        {
        case 1:
            clr_scr();
            train_info_checker();
            break;
        case 2:
            clr_scr();
            train_info_start_end();
            break;
        case 3:
            clr_scr();
            program_exit();
            break;
        default:
            printf("\nInvalid choice!");
            sleep(1);
            clr_scr();
            user_interface();
        }
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
void train_info_start_end()
{
    FILE *fp = fopen("train_record.txt", "r");
    if (fp == NULL)
    {
        printf("\nSorry! Server not working properly.\n");
        return;
    }

    char source_station[50], destination_station[50];
    int date = 0, month = 0, year = 0;

    while (1)
    {
        printf("\nPlease enter source station: ");
        fgets(source_station, 50, stdin);
        source_station[strcspn(source_station, "\n")] = '\0';

        printf("Please enter destination station: ");
        fgets(destination_station, 50, stdin);
        destination_station[strcspn(destination_station, "\n")] = '\0';

        if (strcmp(source_station, destination_station) != 0)
            break;

        printf("\nSource and destination can't be the same. Please re-enter.\n");
    }

    do
    {
        printf("Please enter the date here (DD MM YYYY): ");
        scanf("%d %d %d", &date, &month, &year);
        clear_input();
    } while (!valid_date(date, month, year));

    char *day = day_checker(date, month, year);
    printf("\nDay of journey: %s\n", day);
    sleep(1);
    clr_scr();
    progress_bar_print();
    clr_scr();
    train t_info;
    int found = 0;
    char route_line[1000];

    while (fscanf(fp, "%d|%49[^|]|%d:%d %2s|%d:%d %2s|%49[^|]|%49[^|]|%99[^|]|%d\n",
                  &t_info.train_no,
                  t_info.train_name,
                  &t_info.arrival.hour, &t_info.arrival.minute, t_info.arrival.am_pm,
                  &t_info.depart.hour, &t_info.depart.minute, t_info.depart.am_pm,
                  t_info.start_station,
                  t_info.end_station,
                  t_info.run_days,
                  &t_info.via_count) == 12)
    {
        fgets(route_line, sizeof(route_line), fp);

        int day_match = 0;
        char days_copy[100];
        strcpy(days_copy, t_info.run_days);
        char *dtoken = strtok(days_copy, ",");
        while (dtoken != NULL)
        {
            if (case_insensitive_compare(dtoken, day))
            {
                day_match = 1;
                break;
            }
            dtoken = strtok(NULL, ",");
        }
        if (!day_match)
            continue;

        char *token = strtok(route_line, ";");
        int i = 0;
        while (token != NULL && i < t_info.via_count)
        {
            sscanf(token, "%49[^,],%d:%d %2s,%d:%d %2s",
                   t_info.via[i].station_name,
                   &t_info.via[i].arrival.hour,
                   &t_info.via[i].arrival.minute,
                   t_info.via[i].arrival.am_pm,
                   &t_info.via[i].departure.hour,
                   &t_info.via[i].departure.minute,
                   t_info.via[i].departure.am_pm);
            i++;
            token = strtok(NULL, ";");
        }

        int source_pos = -1, dest_pos = -1;
        int pos = 0;

        if (case_insensitive_compare(t_info.start_station, source_station))
            source_pos = pos;
        if (case_insensitive_compare(t_info.start_station, destination_station))
            dest_pos = pos;
        pos++;

        for (int j = 0; j < t_info.via_count; j++)
        {
            if (case_insensitive_compare(t_info.via[j].station_name, source_station))
                source_pos = pos;
            if (case_insensitive_compare(t_info.via[j].station_name, destination_station))
                dest_pos = pos;
            pos++;
        }

        if (case_insensitive_compare(t_info.end_station, source_station))
            source_pos = pos;
        if (case_insensitive_compare(t_info.end_station, destination_station))
            dest_pos = pos;

        if (source_pos != -1 && dest_pos != -1 && source_pos < dest_pos)
        {
            printf("\nTrain No: %d", t_info.train_no);
            printf("\nTrain Name: %s", t_info.train_name);
            printf("\nJourney Start Time: %02d:%02d %s",
                   t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm);
            printf("\nJourney End Time: %02d:%02d %s",
                   t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm);
            printf("\nRunning Days: %s", t_info.run_days);

            printf("\n\nRoute: %s (Start)\n", t_info.start_station);
            for (int j = 0; j < t_info.via_count; j++)
            {
                printf(" -> %s [%02d:%02d %s  %02d:%02d %s]\n",
                       t_info.via[j].station_name,
                       t_info.via[j].arrival.hour,
                       t_info.via[j].arrival.minute,
                       t_info.via[j].arrival.am_pm,
                       t_info.via[j].departure.hour,
                       t_info.via[j].departure.minute,
                       t_info.via[j].departure.am_pm);
            }
            printf(" -> %s (End)\n", t_info.end_station);
            printf("==========================================================\n");
            found = 1;
        }
    }
    fclose(fp);

    if (!found)
    {
        printf("\nNo trains found between %s and %s on %s.\n",
               source_station, destination_station, day);
        sleep(1);
        clr_scr();
        int b = 0;
        printf("\n1.Check another.");
        printf("\n2.Check trains information.");
        printf("\n3.Exit");
        printf("\nEnter your choice here: ");
        scanf("%d", &b);
        switch (b)
        {
        case 1:
            clr_scr();
            train_info_start_end();
            break;
        case 2:
            clr_scr();
            train_info_checker();
            break;
        case 3:
            clr_scr();
            program_exit();
            break;
        default:
            printf("\nInvalid choice!");
            sleep(1);
            clr_scr();
            user_interface();
        }
    }
}
// ------------------------------------------------------------------------------------------------------------------------------
void train_info_changer()
{
    FILE *fp = fopen("train_record.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("\nSorry! Server not working properly.\n");
        return;
    }

    int n;
    printf("\nEnter Train Number to modify: ");
    scanf("%d", &n);
    clear_input();

    train t_info;
    int found = 0;
    char route_line[1000];

    while (fscanf(fp, "%d|%49[^|]|%d:%d %2s|%d:%d %2s|%49[^|]|%49[^|]|%99[^|]|%d\n",
                  &t_info.train_no,
                  t_info.train_name,
                  &t_info.arrival.hour, &t_info.arrival.minute, t_info.arrival.am_pm,
                  &t_info.depart.hour, &t_info.depart.minute, t_info.depart.am_pm,
                  t_info.start_station,
                  t_info.end_station,
                  t_info.run_days,
                  &t_info.via_count) == 12)
    {
        fgets(route_line, sizeof(route_line), fp);

        if (t_info.train_no == n)
        {
            found = 1;

            printf("\nEnter NEW train name: ");
            fgets(t_info.train_name, 50, stdin);
            t_info.train_name[strcspn(t_info.train_name, "\n")] = '\0';

            do
            {
                printf("Enter NEW journey start time (hour minute am/pm): ");
                scanf("%d %d %2s", &t_info.arrival.hour, &t_info.arrival.minute, t_info.arrival.am_pm);
                clear_input();
            } while (!valid_time(t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm));

            do
            {
                printf("Enter NEW journey end time (hour minute am/pm): ");
                scanf("%d %d %2s", &t_info.depart.hour, &t_info.depart.minute, t_info.depart.am_pm);
                clear_input();
            } while (!valid_time(t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm));

            printf("Enter NEW start station: ");
            fgets(t_info.start_station, 50, stdin);
            t_info.start_station[strcspn(t_info.start_station, "\n")] = '\0';

            printf("Enter NEW end station: ");
            fgets(t_info.end_station, 50, stdin);
            t_info.end_station[strcspn(t_info.end_station, "\n")] = '\0';

            int a;
            printf("Enter the number of running days in the week: ");
            scanf("%d", &a);
            clear_input();

            t_info.run_days[0] = '\0';
            for (int i = 0; i < a; i++)
            {
                char day[15];
                printf("Enter running day %d: ", i + 1);
                fgets(day, sizeof(day), stdin);
                day[strcspn(day, "\n")] = '\0';

                if (strlen(t_info.run_days) + strlen(day) + 2 < sizeof(t_info.run_days))
                {
                    strcat(t_info.run_days, day);
                    if (i < a - 1)
                        strcat(t_info.run_days, ",");
                }
            }

            printf("Enter number of intermediate stations: ");
            scanf("%d", &t_info.via_count);
            clear_input();

            for (int i = 0; i < t_info.via_count; i++)
            {
                printf("\nStation %d name: ", i + 1);
                fgets(t_info.via[i].station_name, 50, stdin);
                t_info.via[i].station_name[strcspn(t_info.via[i].station_name, "\n")] = '\0';

                do
                {
                    printf("Arrival time (hh mm am/pm): ");
                    scanf("%d %d %2s",
                          &t_info.via[i].arrival.hour,
                          &t_info.via[i].arrival.minute,
                          t_info.via[i].arrival.am_pm);
                    clear_input();
                } while (!valid_time(t_info.via[i].arrival.hour, t_info.via[i].arrival.minute, t_info.via[i].arrival.am_pm));

                do
                {
                    printf("Departure time (hh mm am/pm): ");
                    scanf("%d %d %2s",
                          &t_info.via[i].departure.hour,
                          &t_info.via[i].departure.minute,
                          t_info.via[i].departure.am_pm);
                    clear_input();
                } while (!valid_time(t_info.via[i].departure.hour, t_info.via[i].departure.minute, t_info.via[i].departure.am_pm));
            }

            fprintf(temp, "%d|%s|%02d:%02d %s|%02d:%02d %s|%s|%s|%s|%d\n",
                    t_info.train_no,
                    t_info.train_name,
                    t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm,
                    t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm,
                    t_info.start_station,
                    t_info.end_station,
                    t_info.run_days,
                    t_info.via_count);

            for (int i = 0; i < t_info.via_count; i++)
            {
                fprintf(temp, "%s,%02d:%02d %s,%02d:%02d %s;",
                        t_info.via[i].station_name,
                        t_info.via[i].arrival.hour,
                        t_info.via[i].arrival.minute,
                        t_info.via[i].arrival.am_pm,
                        t_info.via[i].departure.hour,
                        t_info.via[i].departure.minute,
                        t_info.via[i].departure.am_pm);
            }
            fprintf(temp, "\n");
        }
        else
        {
            fprintf(temp, "%d|%s|%02d:%02d %s|%02d:%02d %s|%s|%s|%s|%d\n",
                    t_info.train_no,
                    t_info.train_name,
                    t_info.arrival.hour, t_info.arrival.minute, t_info.arrival.am_pm,
                    t_info.depart.hour, t_info.depart.minute, t_info.depart.am_pm,
                    t_info.start_station,
                    t_info.end_station,
                    t_info.run_days,
                    t_info.via_count);
            fputs(route_line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("train_record.txt");
        rename("temp.txt", "train_record.txt");
        clr_scr();
        progress_bar_print();
        printf("\n\nTrain information updated successfully!\n");
        sleep(1);
        clr_scr();
        int b = 0;
        printf("\n1.Add more trains");
        printf("\n2.Change train information");
        printf("\n3.Exit");
        scanf("%d", &b);
        switch (b)
        {
        case 1:
            clr_scr();
            add_train_info();
            break;
        case 2:
            clr_scr();
            train_info_changer();
            break;
        default:
            printf("\nInvalid choice!");
            sleep(1);
            clr_scr();
            admin_checker();
        }
    }
    else
    {
        remove("temp.txt");
        printf("\nNo train with number %d found.\n", n);
    }
}
// ------------------------------------------------------------------------------------------------------------------------------