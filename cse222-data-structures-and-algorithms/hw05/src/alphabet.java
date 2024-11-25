import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

public class alphabet {
    private Set<Character> english_alphabet = new LinkedHashSet<Character>();
    private Map<Character, Map<Character, Character>> map = new HashMap<Character, Map<Character, Character>>();

    public alphabet() {
        // Do not edit this method
        fill_english_alphabet();
        fill_map();
    }

    private void fill_english_alphabet() {
        // Do not edit this method
        for (char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()) {
            english_alphabet.add(c);
        }
    }

    /**
     * Fills the map using the alphabet set.
     * Uses iterators to fill the map.
     */
    private void fill_map() {
		Iterator<Character> alphabetRowIterator = english_alphabet.iterator();
		while (alphabetRowIterator.hasNext()) {
			char rowChar = alphabetRowIterator.next();
			Map<Character, Character> substitutionMap = new HashMap<>();
			Iterator<Character> alphabetColIterator = english_alphabet.iterator();
			char currentChar = rowChar;
			while (alphabetColIterator.hasNext()) {
				char colChar = alphabetColIterator.next();
				substitutionMap.put(colChar, currentChar);
				currentChar = (char) ((currentChar - 'A' + 1) % 26 + 'A');
			}
			map.put(rowChar, substitutionMap);
		}
	}

    /**
     * Prints the Vigenere table.
     */
    public void print_map() {
        System.out.println("*** Vigenere Cipher ***\n\n");
        System.out.println("    " + english_alphabet);
        System.out.print("    ------------------------------------------------------------------------------");
        for (Character k : map.keySet()) {
            System.out.print("\n" + k + " | ");
            System.out.print(map.get(k).values());
        }
        System.out.println("\n");
    }

    /**
     * Returns the Vigenere table map.
     *
     * @return The Vigenere table map.
     */
    public Map<Character, Map<Character, Character>> get_map() {
        return map;
    }
}
