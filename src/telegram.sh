TELEGRAM_BOT_TOKEN="6008907946:AAGt1PkhRN74cJEN9RenaQlcDVOe3IokpMI"
TIME=5
CHAT_ID=637830245
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

TEXT="Job: $CI_JOB_NAME%0AStage: $CI_JOB_STAGE%0AStatus: $CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
curl -s --max-time $TIME -d "chat_id=$CHAT_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
