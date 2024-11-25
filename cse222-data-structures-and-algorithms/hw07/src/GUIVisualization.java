import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.ArrayList;

public class GUIVisualization extends JFrame {
    private List<Integer> dataPointsX;
    private List<Long> addTimes;
    private List<Long> removeTimes;
    private List<Long> searchTimes;
    private List<Long> updateTimes;

    public GUIVisualization(List<Long> addTimes, List<Long> removeTimes, List<Long> searchTimes, List<Long> updateTimes) {
        this.dataPointsX = new ArrayList<>();
        this.addTimes = addTimes;
        this.removeTimes = removeTimes;
        this.searchTimes = searchTimes;
        this.updateTimes = updateTimes;

        for (int i = 0; i < addTimes.size(); i++) {
            dataPointsX.add(i + 1);
        }

        setTitle("Performance Graph Visualization");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        drawGraph(g);
    }

    private void drawGraph(Graphics g) {
        int width = getWidth();
        int height = getHeight();
        int padding = 50;
        int labelPadding = 20;

        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        g2.setColor(Color.WHITE);
        g2.fillRect(padding + labelPadding, padding, width - 2 * padding - labelPadding, height - 2 * padding - labelPadding);
        g2.setColor(Color.BLACK);

        int numberYDivisions = 10;
        long maxYValue = getMaxYValue();
        for (int i = 0; i < numberYDivisions + 1; i++) {
            int x0 = padding + labelPadding;
            int x1 = width - padding;
            int y0 = height - ((i * (height - padding * 2 - labelPadding)) / numberYDivisions + padding);
            int y1 = y0;
            if (addTimes.size() > 0) {
                g2.setColor(Color.LIGHT_GRAY);
                g2.drawLine(padding + labelPadding + 1 + labelPadding, y0, x1, y1);
                g2.setColor(Color.BLACK);
                String yLabel = ((int) ((maxYValue * ((i * 1.0) / numberYDivisions)) * 100)) / 100.0 + "";
                FontMetrics metrics = g2.getFontMetrics();
                int labelWidth = metrics.stringWidth(yLabel);
                g2.drawString(yLabel, x0 - labelWidth - 5, y0 + (metrics.getHeight() / 2) - 3);
            }
        }

        for (int i = 0; i < dataPointsX.size(); i++) {
            if (dataPointsX.size() > 1) {
                int x0 = i * (width - padding * 2 - labelPadding) / (dataPointsX.size() - 1) + padding + labelPadding;
                int x1 = x0;
                int y0 = height - padding - labelPadding;
                int y1 = y0 - 4;
                if ((i % ((int) ((dataPointsX.size() / 20.0)) + 1)) == 0) {
                    g2.setColor(Color.LIGHT_GRAY);
                    g2.drawLine(x0, height - padding - labelPadding - 1 - labelPadding, x1, padding);
                    g2.setColor(Color.BLACK);
                    String xLabel = dataPointsX.get(i) + "";
                    FontMetrics metrics = g2.getFontMetrics();
                    int labelWidth = metrics.stringWidth(xLabel);
                    g2.drawString(xLabel, x0 - labelWidth / 2, y0 + metrics.getHeight() + 3);
                }
                g2.drawLine(x0, y0, x1, y1);
            }
        }

        g2.drawLine(padding + labelPadding, height - padding - labelPadding, padding + labelPadding, padding);
        g2.drawLine(padding + labelPadding, height - padding - labelPadding, width - padding, height - padding - labelPadding);

        drawLegend((Graphics2D) g);

        g2.setColor(Color.BLUE);
        drawGraphLine(g2, addTimes, maxYValue);

        g2.setColor(Color.RED);
        drawGraphLine(g2, removeTimes, maxYValue);

        g2.setColor(Color.GREEN);
        drawGraphLine(g2, searchTimes, maxYValue);

        g2.setColor(Color.ORANGE);
        drawGraphLine(g2, updateTimes, maxYValue);
    }

    private void drawGraphLine(Graphics2D g2, List<Long> times, long maxYValue) {
        int width = getWidth();
        int height = getHeight();
        int padding = 50;
        int labelPadding = 20;
    
        for (int i = 0; i < times.size() - 1; i++) {
            int x1 = i * (width - padding * 2 - labelPadding) / (times.size() - 1) + padding + labelPadding;
            int y1 = height - padding - labelPadding - (int) ((times.get(i) * 1.0) / maxYValue * (height - padding * 2 - labelPadding));
            int x2 = (i + 1) * (width - padding * 2 - labelPadding) / (times.size() - 1) + padding + labelPadding;
            int y2 = height - padding - labelPadding - (int) ((times.get(i + 1) * 1.0) / maxYValue * (height - padding * 2 - labelPadding));
            g2.drawLine(x1, y1, x2, y2);
        }
    }

    private long getMaxYValue() {
        long max = Long.MIN_VALUE;
        for (Long y : addTimes) max = Math.max(max, y);
        for (Long y : removeTimes) max = Math.max(max, y);
        for (Long y : searchTimes) max = Math.max(max, y);
        for (Long y : updateTimes) max = Math.max(max, y);
        return max;
    }

    public static void visualize(List<Long> addTimes, List<Long> removeTimes, List<Long> searchTimes, List<Long> updateTimes) {
        SwingUtilities.invokeLater(() -> {
            GUIVisualization frame = new GUIVisualization(addTimes, removeTimes, searchTimes, updateTimes);
            frame.setVisible(true);
        });
    }


    private void drawLegend(Graphics2D g2) {
        int legendX = getWidth() - 150; // X position for the legend
        int legendY = 80; // Starting Y position for the legend
    
        g2.setColor(Color.BLUE);
        g2.drawLine(legendX, legendY, legendX + 30, legendY);
        g2.drawString("ADD", legendX + 35, legendY + 5);
    
        g2.setColor(Color.RED);
        g2.drawLine(legendX, legendY + 20, legendX + 30, legendY + 20);
        g2.drawString("REMOVE", legendX + 35, legendY + 25);
    
        g2.setColor(Color.GREEN);
        g2.drawLine(legendX, legendY + 40, legendX + 30, legendY + 40);
        g2.drawString("SEARCH", legendX + 35, legendY + 45);

        g2.setColor(Color.ORANGE);
        g2.drawLine(legendX, legendY + 40, legendX + 30, legendY + 40);
        g2.drawString("SEARCH", legendX + 35, legendY + 65);
    
    }
}
