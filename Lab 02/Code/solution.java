package Code;

import java.util.concurrent.Semaphore;

public class solution {
    private static int riders = 0;
    private static Semaphore mutex = new Semaphore(1);
    private static Semaphore multiplex = new Semaphore(50);
    private static Semaphore busSemaphore = new Semaphore(0);
    private static Semaphore allAboard = new Semaphore(0);

    public static void main(String[] args) {
        Bus bus = new Bus();
        Rider[] riders = new Rider[100];

        for (int i = 0; i < riders.length; i++) {
            riders[i] = new Rider(bus);
            riders[i].start();
        }

        bus.start();
    }

    static class Bus extends Thread {
        public void run() {
            try {
                mutex.acquire();
                if (riders > 0) {
                    busSemaphore.release();
                    allAboard.acquire();
                }
                mutex.release();
                depart();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void depart() {
            System.out.println("Bus departed with " + riders + " riders.");
        }
    }

    static class Rider extends Thread {
        private Bus bus;

        public Rider(Bus bus) {
            this.bus = bus;
        }

        public void run() {
            try {
                multiplex.acquire();
                mutex.acquire();
                riders++;
                mutex.release();

                busSemaphore.acquire();
                multiplex.release();

                boardBus();

                mutex.acquire();
                riders--;
                if (riders == 0) {
                    allAboard.release();
                } else {
                    busSemaphore.release();
                }
                mutex.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        private void boardBus() {
            System.out.println("Rider boarded the bus.");
        }
    }
}

// package Code;

// public class solution {
    
// }
