#include <stdio.h>
#include <string.h>

typedef struct {
    int roomNumber;
    int isAvailable;
} Room;

typedef struct {
    int reservationID;
    char guestLastName[50];
    char guestFirstName[50];
    int roomNumber;
    char checkInDate[11];
    char checkOutDate[11];
} Reservation;

void addReservation();
void modifyReservation();
void deleteReservation();
void displayReservations();
int checkRoomAvailability(int roomNumber, char *checkInDate, char *checkOutDate);

Room rooms[100];
Reservation reservations[100];
int reservationCount = 0;

void initializeRooms() {
    for (int i = 0; i < 100; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isAvailable = 1;
    }
}

int main() {
    initializeRooms();

    int choice;
    do {
        printf("\nHotel Room Reservation Management System\n");
        printf("1. Add Reservation\n");
        printf("2. Modify Reservation\n");
        printf("3. Delete Reservation\n");
        printf("4. Display Reservations\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Prevents newline issues

        switch (choice) {
            case 1:
                addReservation();
                break;
            case 2:
                modifyReservation();
                break;
            case 3:
                deleteReservation();
                break;
            case 4:
                displayReservations();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void addReservation() {
    Reservation newReservation;

    printf("Enter Reservation ID: ");
    scanf("%d", &newReservation.reservationID);
    getchar();

    printf("Enter Guest's Last Name: ");
    fgets(newReservation.guestLastName, sizeof(newReservation.guestLastName), stdin);
    newReservation.guestLastName[strcspn(newReservation.guestLastName, "\n")] = '\0';

    printf("Enter Guest's First Name: ");
    fgets(newReservation.guestFirstName, sizeof(newReservation.guestFirstName), stdin);
    newReservation.guestFirstName[strcspn(newReservation.guestFirstName, "\n")] = '\0';

    printf("Enter Room Number: ");
    scanf("%d", &newReservation.roomNumber);

    printf("Enter Check-in Date (YYYY-MM-DD): ");
    scanf("%s", newReservation.checkInDate);

    printf("Enter Check-out Date (YYYY-MM-DD): ");
    scanf("%s", newReservation.checkOutDate);

    if (checkRoomAvailability(newReservation.roomNumber, newReservation.checkInDate, newReservation.checkOutDate)) {
        reservations[reservationCount++] = newReservation;
        printf("Reservation added successfully!\n");
    } else {
        printf("Room is not available for the selected dates.\n");
    }
}

int checkRoomAvailability(int roomNumber, char *checkInDate, char *checkOutDate) {
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].roomNumber == roomNumber) {
            if (!(strcmp(checkOutDate, reservations[i].checkInDate) < 0 || strcmp(checkInDate, reservations[i].checkOutDate) > 0)) {
                return 0; // Room is occupied in this time frame
            }
        }
    }
    return 1;
}

void modifyReservation() {
    int reservationID;
    printf("Enter Reservation ID to modify: ");
    scanf("%d", &reservationID);
    getchar();

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].reservationID == reservationID) {
            printf("Enter new Guest's Last Name: ");
            fgets(reservations[i].guestLastName, sizeof(reservations[i].guestLastName), stdin);
            reservations[i].guestLastName[strcspn(reservations[i].guestLastName, "\n")] = '\0';

            printf("Enter new Guest's First Name: ");
            fgets(reservations[i].guestFirstName, sizeof(reservations[i].guestFirstName), stdin);
            reservations[i].guestFirstName[strcspn(reservations[i].guestFirstName, "\n")] = '\0';

            printf("Enter new Room Number: ");
            scanf("%d", &reservations[i].roomNumber);

            printf("Enter new Check-in Date (YYYY-MM-DD): ");
            scanf("%s", reservations[i].checkInDate);

            printf("Enter new Check-out Date (YYYY-MM-DD): ");
            scanf("%s", reservations[i].checkOutDate);

            printf("Reservation modified successfully!\n");
            return;
        }
    }
    printf("Reservation ID not found.\n");
}

void deleteReservation() {
    int reservationID;
    printf("Enter Reservation ID to delete: ");
    scanf("%d", &reservationID);

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].reservationID == reservationID) {
            for (int j = i; j < reservationCount - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            reservationCount--;
            printf("Reservation deleted successfully!\n");
            return;
        }
    }
    printf("Reservation ID not found.\n");
}

void displayReservations() {
    char filterByDate[11];
    char filterByLastName[50];

    printf("Enter date to filter by (YYYY-MM-DD) or press Enter to skip: ");
    fgets(filterByDate, sizeof(filterByDate), stdin);
    if (filterByDate[0] == '\n') filterByDate[0] = '\0';

    printf("Enter Guest's Last Name to filter by or press Enter to skip: ");
    fgets(filterByLastName, sizeof(filterByLastName), stdin);
    if (filterByLastName[0] == '\n') filterByLastName[0] = '\0';

    int found = 0;
    for (int i = 0; i < reservationCount; i++) {
        if ((strlen(filterByDate) == 0 || strcmp(filterByDate, reservations[i].checkInDate) == 0 || strcmp(filterByDate, reservations[i].checkOutDate) == 0) &&
            (strlen(filterByLastName) == 0 || strcmp(filterByLastName, reservations[i].guestLastName) == 0)) {
            
            printf("Reservation ID: %d\n", reservations[i].reservationID);
            printf("Guest Name: %s %s\n", reservations[i].guestFirstName, reservations[i].guestLastName);
            printf("Room Number: %d\n", reservations[i].roomNumber);
            printf("Check-in Date: %s\n", reservations[i].checkInDate);
            printf("Check-out Date: %s\n", reservations[i].checkOutDate);
            printf("----------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No reservations found matching the criteria.\n");
    }
}