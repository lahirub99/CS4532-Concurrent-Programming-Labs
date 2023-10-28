package Code.solution2;

import java.util.concurrent.Semaphore;
import java.util.Random;

public class solution2 {
    private static Semaphore mutex = new Semaphore(1);
    private static Semaphore bus = new Semaphore(0);
    private static Semaphore boarded = new Semaphore(0);
    private static int waiting = 0;
    private static Random random = new Random();
    private static int bus_mean = 1200; // mean time between bus arrivals is 20 minutes
    private static int rider_mean = 30; // mean time between rider arrivals is 30 seconds

    public static void main(String[] args) {
        Thread riderSpawner = new Thread(new riderSpawner());
        riderSpawner.start();

        Thread busSpawner = new Thread(new busSpawner());
        busSpawner.start();
    }

    static long calulateExponentialDelay(int mean) {
        // Use the mean value to calculate the exponential delay
        return (long) (-mean * Math.log(1 - random.nextDouble()));
    }

    static class riderSpawner implements Runnable {
        @Override
        public void run() {
            while (true) {

                Thread riderThread = new Thread(new Rider());
                riderThread.start();
                // Thread sleep for spawning for the next rider
                try {
                    Thread.sleep(calulateExponentialDelay(rider_mean));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    
    
    static class busSpawner implements Runnable {
        @Override
        public void run() {
            while (true) {
                Thread busThread = new Thread(new Bus());
                busThread.start();
                // Thread sleep for spawning for the next rider
                try {
                    Thread.sleep(calulateExponentialDelay(bus_mean));
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    

    /* The Bus class has a run method that runs in an infinite loop. 
     * 
     * The Bus class has four Semaphores: mutex, bus, boarded, and waiting.
     * 1. The mutex Semaphore is used to protect the waiting variable, which is the number of riders in the boarding area.
     * 2. The bus Semaphore signals when the bus has arrived.
     * 3. The boarded Semaphore signals that a rider has boarded.
     * 4. The waiting variable is an integer that keeps track of how many riders are waiting for the bus.
     */
    static class Bus implements Runnable {
        @Override
        public void run() {
            /* The run method of the Bus class gets the mutex Semaphore and holds it throughout the boarding process.
             * The loop signals each rider in turn and waits for her to board.
             * 
             * By controlling the number of signals, the bus prevents more than 50 riders from boarding. When all the riders have boarded, the bus updates waiting, which is an example of the "I'll do it for you" pattern.
             */
            try {
                mutex.acquire();
                int n = Math.min(waiting, 50);
                arrive(n);
                for (int i = 0; i < n; i++) {
                    bus.release();
                    boarded.acquire();
                }
                waiting = Math.max(waiting - 50, 0);
                mutex.release();
                depart();
                // Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void arrive(int n) {
            System.out.println("Bus arrived when " + waiting + " riders waiting and it gets " + n + " riders on board.");
        }
        private void depart() {
            System.out.println("Bus departed with " + waiting + " riders remaining.");
        }
    }

    /* Rider class has a run method that runs once for each rider.
     * 
     * The Rider class has a Semaphore mutex, which is used to protect the waiting variable.
     */
    static class Rider implements Runnable {
        /*  The run method of the Rider class increments the waiting variable, signals the bus Semaphore, and waits for the boarded Semaphore.
         */
        @Override
        public void run() {
            try {
                mutex.acquire();
                waiting++;
                waitforthebus();
                mutex.release();
                bus.acquire();
                board();
                boarded.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void waitforthebus() {
            System.out.println("Rider waiting." + " Total riders waiting: " + waiting );
        }

        /* 
         * The board method is called when the rider has boarded the bus.
         */
        private void board() {
            System.out.println("Rider boarded");
        }
    }
}
 