import java.util.*;

public class Main {
    public static void main(String[] args) {
        SocialNetworkGraph network = new SocialNetworkGraph();
        Scanner scanner = new Scanner(System.in);
        boolean running = true;

        while (running) {
            System.out.println("===== Social Network Analysis Menu =====");
            System.out.println("1. Add person");
            System.out.println("2. Remove person");
            System.out.println("3. Add friendship");
            System.out.println("4. Remove friendship");
            System.out.println("5. Find shortest path");
            System.out.println("6. Suggest friends");
            System.out.println("7. Count clusters");
            System.out.println("8. Exit");
            System.out.print("Please select an option: ");
            int option = scanner.nextInt();
            scanner.nextLine();  // consume newline

            switch (option) {
                case 1:
                    System.out.print("Enter name: ");
                    String name = scanner.nextLine();
                    System.out.print("Enter age: ");
                    int age = scanner.nextInt();
                    scanner.nextLine();  // consume newline
                    System.out.print("Enter hobbies (comma-separated): ");
                    String hobbiesInput = scanner.nextLine();
                    List<String> hobbies = Arrays.asList(hobbiesInput.split(","));
                    network.addPerson(name, age, hobbies);
                    break;
                case 2:
                    System.out.print("Enter name: ");
                    name = scanner.nextLine();
                    network.removePerson(name);
                    break;
                case 3:
                    System.out.print("Enter first person's name: ");
                    String name1 = scanner.nextLine();
                    System.out.print("Enter second person's name: ");
                    String name2 = scanner.nextLine();
                    network.addFriendship(name1, name2);
                    break;
                case 4:
                    System.out.print("Enter first person's name: ");
                    name1 = scanner.nextLine();
                    System.out.print("Enter second person's name: ");
                    name2 = scanner.nextLine();
                    network.removeFriendship(name1, name2);
                    break;
                case 5:
                    System.out.print("Enter start person's name: ");
                    String startName = scanner.nextLine();
                    System.out.print("Enter end person's name: ");
                    String endName = scanner.nextLine();
                    network.findShortestPath(startName, endName);
                    break;
                case 6:
                    System.out.print("Enter person's name: ");
                    name = scanner.nextLine();
                    System.out.print("Enter maximum number of friends to suggest: ");
                    int maxSuggestions = scanner.nextInt();
                    network.suggestFriends(name, maxSuggestions);
                    break;
                case 7:
                    network.countClusters();
                    break;
                case 8:
                    running = false;
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
                    break;
            }
        }

        scanner.close();
    }
}
