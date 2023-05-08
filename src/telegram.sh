TELEGRAM_BOT_TOKEN="6008907946:AAGt1PkhRN74cJEN9RenaQlcDVOe3IokpMI"
TIME=5
CHAT_ID=637830245

CI_JOB_NAME="cat"
CI_JOB_STAGE="test"
CI_PIPELINE_ID=12345
CI_COMMIT_REF_SLUG="develop"
CI_PROJECT_NAME="DO6 CI/CD"
CI_JOB_STATUS="success"
CI_PROJECT_URL="https://repos.21-school.ru/students/DO6_CICD.ID_356283/loretath_student.21_school.ru/DO6_CICD-1"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"



TEXT="Job: $CI_JOB_NAME%0AStage: $CI_JOB_STAGE%0AStatus: $CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
curl -s --max-time $TIME -d "chat_id=$CHAT_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
