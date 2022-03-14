
# job = rq.Queue().fetch_job(job_id)
# ...
if job.is_failed:
    if job.exc_info:
        response["message"] = "".join(
            job.exc_info.strip().split("\n")[-1].split(":")[1:]
        ).strip()
    else:
        response["message"] = "failed, but I have no message..."
