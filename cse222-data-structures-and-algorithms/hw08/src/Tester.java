import java.util.*;

/**
 * THIS class is used to test the functionality of the SocialNetworkGraph class.
 * It demonstrates adding and removing people, managing friendships, finding the shortest path,
 * counting clusters, and suggesting friends in the social network.
 */
public class Tester {

    /**
     * The main method that runs the test cases for the SocialNetworkGraph class.
     * It includes adding and removing people, managing friendships, finding shortest paths,
     * counting clusters, and suggesting friends.
     * 
     * @param args command-line arguments (not used)
     */
    public static void main(String[] args) {
        SocialNetworkGraph network = new SocialNetworkGraph();

        // Adding people
        network.addPerson("Ali Kaya", 25, Arrays.asList("kitap okumak", "yürüyüş yapmak", "yemek pişirmek"));
        network.addPerson("Ayşe Yılmaz", 22, Arrays.asList("yüzmek", "yemek pişirmek"));
        network.addPerson("Mehmet Demir", 27, Arrays.asList("yürüyüş yapmak", "resim yapmak"));
        network.addPerson("Fatma Çelik", 30, Arrays.asList("kitap okumak", "yüzmek"));
        network.addPerson("Emre Aydın", 28, Arrays.asList("koşmak", "yüzmek"));
        network.addPerson("Zeynep Kara", 26, Arrays.asList("kitap okumak", "yürüyüş yapmak"));
        network.addPerson("Murat Öz", 29, Arrays.asList("yüzmek", "yemek pişirmek"));
        network.addPerson("Elif Doğan", 24, Arrays.asList("resim yapmak", "koşmak"));
        network.addPerson("Ahmet Ak", 31, Arrays.asList("yürüyüş yapmak", "yüzmek"));
        network.addPerson("Cemre Kır", 23, Arrays.asList("yemek pişirmek", "kitap okumak"));
        System.out.println();

        // Adding friendships
        network.addFriendship("Ali Kaya", "Ayşe Yılmaz");
        network.addFriendship("Ali Kaya", "Mehmet Demir");
        network.addFriendship("Ayşe Yılmaz", "Fatma Çelik");
        network.addFriendship("Emre Aydın", "Zeynep Kara");
        network.addFriendship("Murat Öz", "Elif Doğan");
        network.addFriendship("Ahmet Ak", "Cemre Kır");
        network.addFriendship("Mehmet Demir", "Murat Öz");
        network.addFriendship("Ali Kaya", "Cemre Kır");
        network.addFriendship("Fatma Çelik", "Ahmet Ak");
        System.out.println();

        // Finding shortest path 
        network.findShortestPath("Ali Kaya", "Fatma Çelik");
        System.out.println();
        network.findShortestPath("Emre Aydın", "Murat Öz");
        System.out.println();

        // Counting clusters
        network.countClusters();
        System.out.println();

        // Suggesting friends
        network.suggestFriends("Ali Kaya", 3);
        System.out.println();
        network.suggestFriends("Murat Öz", 3);
        System.out.println();

        // Removal of a person
        network.removePerson("Zeynep Kara");
        System.out.println();

        // Removal of a friendship
        network.removeFriendship("Ali Kaya", "Ayşe Yılmaz");
        System.out.println();

        // Re-counting clusters after removals
        network.countClusters();
        System.out.println();

        // Adding more friendships
        network.addFriendship("Emre Aydın", "Ayşe Yılmaz");
        network.addFriendship("Murat Öz", "Fatma Çelik");
        network.addFriendship("Ahmet Ak", "Elif Doğan");
        System.out.println();

        // Final cluster count
        network.countClusters();
        System.out.println();

        // Suggesting friends after changes
        network.suggestFriends("Ali Kaya", 3);
        System.out.println();
        network.suggestFriends("Emre Aydın", 3);
        System.out.println();
    }
}