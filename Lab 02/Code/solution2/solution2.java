/* 
 * The Senate Bus problem:
This problem was originally based on the Senate bus at Wellesley College. Riders
come to a bus stop and wait for a bus. When the bus arrives, all the waiting
riders invoke boardBus, but anyone who arrives while the bus is boarding has
to wait for the next bus. The capacity of the bus is 50 people; if there are more
than 50 people waiting, some will have to wait for the next bus.
When all the waiting riders have boarded, the bus can invoke depart. If the
bus arrives when there are no riders, it should depart immediately.

Puzzle: Write synchronization code that enforces all of these constraints.

 * 
 * Solution: 
Grant Hutchins came up with this solution, which uses fewer variables than the
previous one, and doesn’t involve passing around any mutexes. Here are the
variables:
Bus problem solution #2 (initialization)
1 waiting = 0
2 mutex = new Semaphore (1)
3 bus = new Semaphore (0)
4 boarded = new Semaphore (0)

waiting is the number of riders in the boarding area, which is protected by
mutex. bus signals when the bus has arrived; boarded signals that a rider has
boarded.

Here is the code for the bus.

Bus problem solution (bus):
1 mutex . wait ()
2 n = min ( waiting , 50)
3 for i in range (n ):
4 bus . signal ()
5 boarded . wait ()
6
7 waiting = max ( waiting -50 , 0)
8 mutex . signal ()
9
10 depart ()

The bus gets the mutex and holds it throughout the boarding process. The
loop signals each rider in turn and waits for her to board. By controlling the
number of signals, the bus prevents more than 50 riders from boarding.
When all the riders have boarded, the bus updates waiting, which is an
example of the "I'll do it for you" pattern.

The code for the riders uses two simple patterns: a mutex and a rendezvous.

Bus problem solution (riders):
1 mutex . wait ()
2 waiting += 1
3 mutex . signal ()
4
5 bus . wait ()
6 board ()
7 boarded . signal ()

 */

package Code.solution2;

import java.util.concurrent.Semaphore;

public class solution2 {
    private static Semaphore mutex = new Semaphore(1);
    private static Semaphore bus = new Semaphore(0);
    private static Semaphore boarded = new Semaphore(0);
    private static int waiting = 0;

    public static void main(String[] args) {
        Thread busThread = new Thread(new Bus());
        busThread.start();

        for (int i = 1; i <= 50; i++) {
            Thread riderThread = new Thread(new Rider(i));
            riderThread.start();
        }
    }

    static class Bus implements Runnable {
        @Override
        public void run() {
            while (true) {
                try {
                    mutex.acquire();
                    int n = Math.min(waiting, 50);
                    for (int i = 0; i < n; i++) {
                        bus.release();
                        boarded.acquire();
                    }
                    waiting = Math.max(waiting - 50, 0);
                    mutex.release();
                    depart();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        private void depart() {
            System.out.println("Bus departed with " + Math.min(waiting, 50) + " riders");
        }
    }

    static class Rider implements Runnable {
        private final int id;

        public Rider(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            try {
                mutex.acquire();
                waiting++;
                mutex.release();
                bus.acquire();
                board();
                boarded.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void board() {
            System.out.println("Rider " + id + " boarded");
        }
    }
}