int (FILE* log, Event ev, int cpu_qlen, int d1_qlen, int d2_qlen)
{
    return fprintf(log, "%d,%d,%d,%d,%d,%d\n",
        ev.timestamp, ev.jobtype, ev.serial, cpu_qlen, d1_qlen, d2_qlen);
}