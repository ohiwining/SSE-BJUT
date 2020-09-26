import java.awt.*;
import java.awt.event.*;

public class test implements MouseListener,MouseMotionListener,WindowListener
{
    private Frame f;
    private TextField tf;
    public static void main(String [] args) {
        test MultiListener = new test();
        MultiListener.execute();
    }
    public void execute() {
        f=new Frame("test for multiListener");
        f.add(new Label("click and drag the mouse"),"North");
        tf=new TextField(30);
        f.add(tf,"South");
        f.addMouseListener(this);
        f.addMouseMotionListener(this);
        f.addWindowListener(this);
        f.setSize(300,200);
        f.setVisible(true);
    }
    public void mouseClicked(MouseEvent mouseEvent) {

    }
    public void mousePressed(MouseEvent mouseEvent) { }
    public void mouseReleased(MouseEvent mouseEvent) { }
    public void mouseEntered(MouseEvent mouseEvent) {
        String s="Mouse has entered";
        tf.setText(s);
    }
    public void mouseExited(MouseEvent mouseEvent) {
        String s="Mouse has exited";
        tf.setText(s);
    }
    public void mouseDragged(MouseEvent mouseEvent) {
        String s="Mouse x:"+mouseEvent.getX()+" Mouse y:"+mouseEvent.getY();
        tf.setText(s);
    }
    public void mouseMoved(MouseEvent mouseEvent) { }
    public void windowOpened(WindowEvent windowEvent) { }
    public void windowClosing(WindowEvent windowEvent) {
        System.exit(0);
    }
    public void windowClosed(WindowEvent windowEvent) { }
    public void windowIconified(WindowEvent windowEvent) { }
    public void windowDeiconified(WindowEvent windowEvent) { }
    public void windowActivated(WindowEvent windowEvent) { }
    public void windowDeactivated(WindowEvent windowEvent) { }
}

