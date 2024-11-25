import java.util.*;

/**
 * Represents a social network graph.
 */
public class SocialNetworkGraph {
    Map<String, Person> people = new HashMap<>();
    Map<Person, List<Person>> friendships = new HashMap<>();

    /**
     * Adds a person to the social network.
     *
     * @param name    the name of the person
     * @param age     the age of the person
     * @param hobbies the hobbies of the person
     */
    public void addPerson(String name, int age, List<String> hobbies) {
        Person person = new Person(name, age, hobbies);
        people.put(name, person);
        friendships.put(person, new ArrayList<>());
        System.out.println("Person added: " + person);
    }

    /**
     * Removes a person from the social network.
     *
     * @param name the name of the person to remove
     */
    public void removePerson(String name) {
        // Retrieve the person object from the map
        Person person = people.remove(name);
        if (person != null) {
            // Remove the person from the friendships map
            friendships.remove(person);
            // Remove this person from all other people's friend lists
            for (List<Person> friends : friendships.values()) {
                friends.remove(person);
            }
            System.out.println("Person removed: " + person);
        } else {
            System.out.println("Person not found in the network.");
        }
    }

    /**
     * Adds a friendship between two people in the social network.
     *
     * @param name1 the name of the first person
     * @param name2 the name of the second person
     */
    public void addFriendship(String name1, String name2) {
        Person person1 = people.get(name1);
        Person person2 = people.get(name2);
        if (person1 != null && person2 != null) {
            friendships.get(person1).add(person2);
            friendships.get(person2).add(person1);
            System.out.println("Friendship added between " + person1.name + " and " + person2.name);
        } else {
            System.out.println("One or both persons not found in the network.");
        }
    }

    /**
     * Removes a friendship between two people in the social network.
     *
     * @param name1 the name of the first person
     * @param name2 the name of the second person
     */
    public void removeFriendship(String name1, String name2) {
        // Retrieve the person objects from the map
        Person person1 = people.get(name1);
        Person person2 = people.get(name2);
        if (person1 != null && person2 != null) {
            // Remove each person from the other's friend list
            friendships.get(person1).remove(person2);
            friendships.get(person2).remove(person1);
            System.out.println("Friendship removed between " + person1.name + " and " + person2.name);
        } else {
            System.out.println("One or both persons not found in the network.");
        }
    }

    /**
     * Finds the shortest path between two people using Breadth-First Search (BFS).
     *
     * @param startName the name of the start person
     * @param endName   the name of the end person
     */
    public void findShortestPath(String startName, String endName) {
        // Retrieve the start and end person objects from the map
        Person start = people.get(startName);
        Person end = people.get(endName);
        if (start == null || end == null) {
            System.out.println("One or both persons not found in the network.");
            return;
        }

        // Map to store the previous node in the path
        Map<Person, Person> prev = new HashMap<>();
        // Queue for BFS
        Queue<Person> queue = new LinkedList<>();
        // Set to keep track of visited nodes
        Set<Person> visited = new HashSet<>();
        queue.add(start);
        visited.add(start);

        // BFS algorithm
        while (!queue.isEmpty()) {
            Person current = queue.poll();
            if (current.equals(end)) {
                printPath(start, end, prev);
                return;
            }

            // Visit all neighbors of the current node
            for (Person neighbor : friendships.get(current)) {
                if (!visited.contains(neighbor)) {
                    queue.add(neighbor);
                    visited.add(neighbor);
                    prev.put(neighbor, current);
                }
            }
        }
        System.out.println("No connection between " + startName + " and " + endName);
    }

    /**
     * Prints the path from the start person to the end person.
     *
     * @param start the start person
     * @param end   the end person
     * @param prev  the map of previous persons in the path
     */
    private void printPath(Person start, Person end, Map<Person, Person> prev) {
        List<Person> path = new ArrayList<>();
        for (Person at = end; at != null; at = prev.get(at)) {
            path.add(at);
        }
        Collections.reverse(path);
        System.out.println("Shortest path: " + path);
    }

    /**
     * Counts and prints clusters (connected components) in the social network using BFS.
     */
    public void countClusters() {
        // Set to keep track of visited nodes
        Set<Person> visited = new HashSet<>();
        int clusterCount = 0;
        // Iterate through all people in the network
        for (Person person : people.values()) {
            if (!visited.contains(person)) {
                clusterCount++;
                List<Person> cluster = new ArrayList<>();
                bfs(person, visited, cluster);
                System.out.println("Cluster " + clusterCount + ":");
                // Print all people in the current cluster
                for (Person p : cluster) {
                    System.out.println(p.name);
                }
            }
        }
        System.out.println("Number of clusters found: " + clusterCount);
    }

    /**
     * Performs a Breadth-First Search (BFS) to explore all people connected to the start person.
     *
     * @param start    the start person
     * @param visited  the set of visited people
     * @param cluster  the list of people in the current cluster
     */
    private void bfs(Person start, Set<Person> visited, List<Person> cluster) {
        Queue<Person> queue = new LinkedList<>();
        queue.add(start);
        visited.add(start);

        while (!queue.isEmpty()) {
            Person current = queue.poll();
            cluster.add(current);

            for (Person neighbor : friendships.get(current)) {
                if (!visited.contains(neighbor)) {
                    queue.add(neighbor);
                    visited.add(neighbor);
                }
            }
        }
    }

    /**
     * Suggests friends for a person based on mutual friends and common hobbies.
     *
     * @param name           the name of the person for whom to suggest friends
     * @param maxSuggestions the maximum number of friend suggestions
     */
    public void suggestFriends(String name, int maxSuggestions) {
        // Retrieve the person object from the map
        Person person = people.get(name);
        if (person == null) {
            System.out.println("Person not found in the network.");
            return;
        }

        // Maps to store scores, mutual friends, and common hobbies
        Map<Person, Double> scores = new HashMap<>();
        Map<Person, Integer> mutualFriendsMap = new HashMap<>();
        Map<Person, Integer> commonHobbiesMap = new HashMap<>();
        
        // Iterate through all people in the network
        for (Person potentialFriend : people.values()) {
            if (potentialFriend.equals(person) || friendships.get(person).contains(potentialFriend)) {
                continue;
            }
            int mutualFriends = 0;
            int commonHobbies = 0;

            // Count mutual friends
            for (Person friend : friendships.get(person)) {
                if (friendships.get(potentialFriend).contains(friend)) {
                    mutualFriends++;
                }
            }

            // Count common hobbies
            for (String hobby : person.hobbies) {
                if (potentialFriend.hobbies.contains(hobby)) {
                    commonHobbies++;
                }
            }

            // Calculate score
            double score = mutualFriends + (commonHobbies * 0.5);
            scores.put(potentialFriend, score);
            mutualFriendsMap.put(potentialFriend, mutualFriends);
            commonHobbiesMap.put(potentialFriend, commonHobbies);
        }

        // Sort potential friends by score
        List<Map.Entry<Person, Double>> sortedCandidates = new ArrayList<>(scores.entrySet());
        sortedCandidates.sort((e1, e2) -> Double.compare(e2.getValue(), e1.getValue()));

        // Print top N friend suggestions
        System.out.println("Suggested friends for " + person.name + ":");
        for (int i = 0; i < Math.min(maxSuggestions, sortedCandidates.size()); i++) {
            Map.Entry<Person, Double> entry = sortedCandidates.get(i);
            Person suggestedPerson = entry.getKey();
            double score = entry.getValue();
            int mutualFriends = mutualFriendsMap.get(suggestedPerson);
            int commonHobbies = commonHobbiesMap.get(suggestedPerson);
            System.out.println(suggestedPerson.name + " (Score: " + score + ", " + mutualFriends + " mutual friends, " + commonHobbies + " common hobbies)");
        }
    }
}
