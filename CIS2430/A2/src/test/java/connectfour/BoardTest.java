package connectfour;

import java.util.ArrayList;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class BoardTest{
    private Board tester;

    @Before
    public void setup(){
        //set up for the test
        tester = new Board();

    }

    @Test
    public void testBoardConstructor() {
        Board testConstructor = new Board();
        ArrayList<Integer> expected = new ArrayList<Integer>();

        for (int i=0; i<42; i++) {
            expected.add(0);
        }

        assertEquals(42, testConstructor.getBoard().size());
        assertEquals(expected,testConstructor.getBoard());
    }

    @Test
    public void testCheckColumnFullColumn() {
        int actual;

        tester.setBoard(0,1);
        tester.setBoard(7,2);
        tester.setBoard(14,1);
        tester.setBoard(21,2);
        tester.setBoard(28,1);
        tester.setBoard(35,2);

        actual = tester.checkColumn(1);

        assertEquals(0,actual);
    }

    @Test
    public void testCheckColumnEmptyColumn() {
        int actual;

        actual = tester.checkColumn(7);

        assertEquals(1,actual);
    }

    @Test
    public void testCheckColumnHalfFullColumn() {
        int actual;

        tester.setBoard(38,2);
        tester.setBoard(31,1);
        tester.setBoard(24,2);

        actual = tester.checkColumn(4);

        assertEquals(1,actual);
    }

    @Test
    public void testCheckBoardFullFull() {
        int actual;

        for (int i=0; i<42; i++) {
            tester.setBoard(i,1);
        }

        actual = tester.checkBoardFull();

        assertEquals(0,actual);
    }

    @Test
    public void testCheckBoardFullEmpty() {
        int actual;

        actual = tester.checkBoardFull();

        assertEquals(1,actual);
    }

    @Test
    public void testCheckBoardFullHalfFull() {
        int actual;

        for (int i=21; i<21; i++) {
            tester.setBoard(i,2);
        }

        actual = tester.checkBoardFull();

        assertEquals(1,actual);
    }

    @Test
    public void testGetWinConditionsRowWin() {
        int actual;

        tester.setBoard(36,1);
        tester.setBoard(37,1);
        tester.setBoard(38,1);
        tester.setBoard(39,1);

        actual = tester.getWinConditions();

        assertEquals(1,actual);
    }

    @Test
    public void testGetWinConditionsColumnWin() {
        int actual;

        tester.setBoard(5,2);
        tester.setBoard(12,2);
        tester.setBoard(19,2);
        tester.setBoard(26,2);
        
        actual = tester.getWinConditions();

        assertEquals(1,actual);
    }

    @Test
    public void testGetWinConditionsRightDiagonalWin() {
        int actual;

        tester.setBoard(3,1);
        tester.setBoard(11,1);
        tester.setBoard(19,1);
        tester.setBoard(27,1);

        actual = tester.getWinConditions();

        assertEquals(1,actual);
    }

    @Test
    public void testGetWinConditionsLeftDiagonalWin() {
        int actual;

        tester.setBoard(19,2);
        tester.setBoard(25,2);
        tester.setBoard(31,2);
        tester.setBoard(37,2);

        actual = tester.getWinConditions();

        assertEquals(1,actual);
    }

    @Test
    public void testGetWinConditionsNoWin() {
        int actual;

        tester.setBoard(36,1);
        tester.setBoard(37,2);

        actual = tester.getWinConditions();

        assertEquals(0,actual);
    }

    @Test
    public void testChangeBoardEmptyColumn() {
        ArrayList<Integer> expected = new ArrayList<Integer>();

        for (int i=0; i<41; i++) {
            expected.add(0);
        }

        expected.add(1);

        tester.changeBoard(7,1);

        assertEquals(expected,tester.getBoard());
    }

    @Test
    public void testChangeBoardNotEmptyColumn() {
        ArrayList<Integer> expected = new ArrayList<Integer>();

        for (int i=0; i<42; i++) {
            expected.add(0);
        }
        expected.set(30, 2);
        expected.set(37, 1);

        tester.setBoard(37,1);
        tester.changeBoard(3,2);

        assertEquals(expected,tester.getBoard());
    }
}