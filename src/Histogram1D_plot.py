import matplotlib.pyplot as plt
import csv
import sys

if len(sys.argv)!=2:
    print("Usage: python plot_histogram.py <csv_file>")
    sys.exit(1)

csv_file=sys.argv[1]

bin_center=[]
counts=[]
errors=[]

with open(csv_file,"r") as f:
    reader=csv.DictReader(f)
    for row in reader:
        if row["count"]!="N/A":
            bin_start=float(row["bin_start"])
            bin_end=float(row["bin_end"])
            center=(bin_start+bin_end)/2
            bin_center.append(center)
            counts.append(float(row["count"]))
            errors.append(float(row["error"]))

plt.errorbar(bin_center,counts,yerr=errors,fmt='o',capsize=3,label='Histogram1D')
plt.xlabel("Value")
plt.ylabel("Count")
plt.title("Histogram1D with errors")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("Histogram1D_plot.png")
plt.show()