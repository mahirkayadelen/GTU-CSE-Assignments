
public class driver {
    public static void main(String[] args) {

        dataset DataCollection = new dataset();

        Player playerOne = new Player("First Player");
        Player playerTwo = new Player("Second Player");
        Player playerThree = new Player("Third Player");
        Viewer viewerOne = new Viewer("First Viewer");
        Viewer viewerTwo = new Viewer("Second Viewer");

        DataCollection.register(playerOne);
        DataCollection.register(playerOne);  // Testing if the same object can be registered multiple times

        DataCollection.register(playerTwo);
        DataCollection.register(playerThree);
        DataCollection.register(viewerOne);
        DataCollection.register(viewerTwo);

        System.out.println("Dataset Before Removing playerThree:");
        System.out.println(DataCollection);
        DataCollection.remove_observer(playerThree); //  Checking if the remove_observer() works 
        System.out.println("Dataset After Removing playerThree:");
        System.out.println(DataCollection);

        System.out.println("Adding new image objects to dataset");
        DataCollection.add(new image("imageOne", 250, 120));
        DataCollection.add(new image("imageTwo", 140, 280));
        DataCollection.add(new image("imageThree", 2, 3));
        DataCollection.add(new image("imageFour", 2, 20));
        DataCollection.add(new image("imageFive", 1100, 1100));

        System.out.println("Adding new audio objects to dataset");
        DataCollection.add(new audio("audioOne", 16.3));
        DataCollection.add(new audio("audioTwo", 7.2));
        DataCollection.add(new audio("audioThree", 32));

        System.out.println("Adding new video objects to dataset");
        DataCollection.add(new video("videoOne", 12, 8, 3));
        DataCollection.add(new video("videoTwo", 105, 4, 16.8));
        DataCollection.add(new video("videoThree", 18, 310, 130.5));

        System.out.println("Adding new text objects to dataset");
        DataCollection.add(new text("textOne"));
        DataCollection.add(new text("textTwo"));
        DataCollection.add(new text("textThree"));

        System.out.println("Testing playerThree:");
        DataCollection.register(playerThree);
        playerThree.showList();
        DataCollection.remove_observer(playerThree);

        System.out.println("checking every player and viewer:");
        System.out.println("playerOne->showList()");
        playerOne.showList();
        System.out.println("viewerOne->showList()");
        viewerOne.showList();
        System.out.println("playerTwo->showList()");
        playerTwo.showList();
        System.out.println("viewerTwo->showList()");
        viewerTwo.showList();

        System.out.println("Testing next() on playerOne:");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());
        playerOne.next("audio");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());
        playerOne.next("video");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());
        playerOne.next("audio");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());
        playerOne.next("video");
        playerOne.next("video");
        playerOne.next("video");
        playerOne.next("audio");
        playerOne.next("a");

        System.out.println("Testing previous() on playerOne:");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());
        playerOne.previous("video");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());
        playerOne.previous("audio");
        System.out.println("playerOne currently playing: " + playerOne.currently_playing());

        System.out.println("\nTesting next() on viewerOne:");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());
        viewerOne.next("image");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());
        viewerOne.next("text");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());
        viewerOne.next("image");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());
        viewerOne.next("a");
        System.out.println("Testing previous() on viewerOne:");
        viewerOne.previous("image");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());
        viewerOne.previous("text");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());
        viewerOne.previous("image");
        System.out.println("viewerOne currently playing: " + viewerOne.currently_viewing());

        playable playableMedia = (playable) playerOne.currently_playing();
        playableMedia.info();
        DataCollection.remove(playableMedia);
        System.out.println("playerOne without audioThree: ");
        System.out.println("Player1.showlist->");
        playerOne.showList();
        System.out.println("Currentlyplaying->");
        System.out.println(playerOne.currently_playing());
        playerOne.previous("audio");
        System.out.println("Currentlyplaying->");
        System.out.println(playerOne.currently_playing());
        playableMedia = (playable) playerOne.currently_playing();
        DataCollection.remove(playableMedia);
        System.out.println("Player1.showlist->");
        playerOne.showList();
        System.out.println("Currentlyplaying->");
        System.out.println(playerOne.currently_playing());

        nonPlayable nonPlayableMedia = (nonPlayable)viewerOne.currently_viewing();
        nonPlayableMedia.info();
        System.out.println("Removed nonPlayableMedia (imageFour)");
        DataCollection.remove(nonPlayableMedia);
        System.out.println("Viewer1.showlist->");
        viewerOne.showList();
        System.out.println("Currentlyviewing->");
        System.out.println(viewerOne.currently_viewing());
        viewerOne.previous("image");
        System.out.println("Currentlyviewing->");   
        System.out.println(viewerOne.currently_viewing());
        nonPlayableMedia = (nonPlayable) viewerOne.currently_viewing();
        System.out.println("Removed imageThree");
        DataCollection.remove(nonPlayableMedia);
        System.out.println("Currentlyviewing->");
        System.out.println(viewerOne.currently_viewing());
    }

}