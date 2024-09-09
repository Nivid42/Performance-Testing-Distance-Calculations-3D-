# Performance-Testing-Distance-Calculations--3D-
 

<h2 align="left">Information</h2>
<p>Even if the Time consumed is not relevant in this field (for what it is inteded), it was nice to build a PT for such Methods to find out which one is faster. <br> <strong>What it does is</strong>, it lets you define your method, and then call the <strong>measure time method</strong> on it to calc the <strong>Time</strong> and <strong>Result</strong>.</p>


<h2 align="left">Usage</h2>
<strong>Steps:</strong> <br>
1. Paste in your Method which you wanna Test. <br>
<br>
<pre><code>
float DistanceCalculator::distance_v3(const Vector3& point1, const Vector3& point2) {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) +
        (point1.y - point2.y) * (point1.y - point2.y) +
        (point1.z - point2.z) * (point1.z - point2.z));
}
</code></pre>

2. Call the measure_time method with the given parameters <br>
<pre><code>
    measure_time(&calculator, &DistanceCalculator::distance_v3, "distance_v3", num_iterations, measurements);
</code>
</pre>
3. Start <br>
